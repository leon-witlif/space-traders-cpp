#include "Window.h"

static bool updateAgent = false;
static bool updateContracts = false;
static bool updateShips = false;

static ImGuiWindowFlags DefaultWindowFlags = ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoBringToFrontOnFocus;

SpaceTraders::Window::Window(HttpClient& client, const std::string& agentToken)
    : m_Client(client), m_AgentToken(agentToken)
{
    if (!glfwInit())
    {
        std::cerr << "Could not initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(1280, 720, "SpaceTraders", nullptr, nullptr);

    if (!m_Window)
    {
        std::cerr << "Could not create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    ImGui::CreateContext();

    // ImGuiIO& io = ImGui::GetIO();
    // io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf", 15);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init();
}

SpaceTraders::Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void SpaceTraders::Window::RunWindowLoop()
{
    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

        if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ShowGlobalWindow();
        ShowAgentWindow();
        ShowContractWindow();
        ShowShipWindow();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(m_Window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
    }
}

void SpaceTraders::Window::ShowGlobalWindow()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    static auto status = Endpoint::Global::GetStatus(m_Client);

    ImGui::Begin("Global", nullptr, DefaultWindowFlags);

    if (status)
    {
        ImGui::Text("Status: %s", status->status.c_str());
        ImGui::Text("Version: %s", status->version.c_str());
        ImGui::Text("ResetDate: %s", status->resetDate.c_str());
        ImGui::TextWrapped("Description: %s", status->description.c_str());
    }
    else
    {
        ImGui::Text("Unable to load Status...");
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowAgentWindow()
{
    ImGui::SetNextWindowPos(ImVec2(640, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    static auto agent = Endpoint::Agent::GetAgent(m_Client, m_AgentToken);

    ImGui::Begin("Agent", nullptr, DefaultWindowFlags);

    if (agent)
    {
        ImGui::Text("Symbol: %s", agent->symbol.c_str());
        ImGui::Text("Headquarters: %s", agent->headquarters.c_str());
        ImGui::Text("Credits: %li", agent->credits);
        ImGui::Text("StartingFaction: %s", agent->startingFaction.c_str());
        ImGui::Text("ShipCount: %i", agent->shipCount);
    }
    else
    {
        ImGui::Text("Unable to load Agent...");
    }

    if (updateAgent)
    {
        updateAgent = false;
        agent = Endpoint::Agent::GetAgent(m_Client, m_AgentToken);
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowContractWindow()
{
    ImGui::SetNextWindowPos(ImVec2(0, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    static auto contracts = Endpoint::Contract::ListContracts(m_Client, m_AgentToken);

    ImGui::Begin("Contract", nullptr, DefaultWindowFlags);

    if (contracts.size())
    {
        ImGui::BeginTabBar("Contracts");

        for (const auto& contract : contracts)
        {
            if (ImGui::BeginTabItem(contract.type.c_str()))
            {
                ImGui::Text("FactionSymbol: %s", contract.factionSymbol.c_str());
                ImGui::Text("Deadline: %s", contract.terms.deadline.c_str());
                ImGui::Text("Payment: %i on accept, %i on fulfill", contract.terms.payment.onAccepted, contract.terms.payment.onFulfilled);

                for (const auto& deliverGood : contract.terms.deliver)
                {
                    ImGui::BulletText("%i / %i %s at %s", deliverGood.unitsFulfilled, deliverGood.unitsRequired, deliverGood.tradeSymbol.c_str(), deliverGood.destinationSymbol.c_str());
                }

                ImGui::Text("Accepted: %s", contract.accepted ? "Yes" : "No");
                ImGui::Text("Fulfilled: %s", contract.fulfilled ? "Yes" : "No");

                if (!contract.accepted)
                {
                    ImGui::Text("DeadlineToAccept: %s", contract.deadlineToAccept.c_str());

                    if (ImGui::Button("Accept"))
                    {
                        Endpoint::Contract::AcceptContract(m_Client, m_AgentToken, contract);
                        updateAgent = updateContracts = true;
                    }
                }

                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }
    else
    {
        ImGui::Text("Unable to load Contracts...");
    }

    if (updateContracts)
    {
        updateContracts = false;
        contracts = Endpoint::Contract::ListContracts(m_Client, m_AgentToken);
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowShipWindow()
{
    ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    static auto ships = Endpoint::Fleet::ListShips(m_Client, m_AgentToken);

    ImGui::Begin("Ship", nullptr, DefaultWindowFlags);

    if (ships.size())
    {
        ImGui::BeginTabBar("Ships");

        for (const auto& ship : ships)
        {
            if (ImGui::BeginTabItem(ship.symbol.c_str()))
            {
                ImGui::Text("Role: %s", ship.registration.role.c_str());
                ImGui::Text("Waypoint: %s", ship.nav.waypointSymbol.c_str());
                if (ship.nav.status == "IN_TRANSIT")
                {
                    ImGui::Text("Traveling from %s to %s", ship.nav.route.origin.symbol.c_str(), ship.nav.route.destination.symbol.c_str());
                    ImGui::Text("Arrival at %s", ship.nav.route.arrival.c_str());
                }
                ImGui::Text("Status: %s", ship.nav.status.c_str());

                ImGui::AlignTextToFramePadding();
                ImGui::Text("FlightMode:");
                static const char* flightModes[] = {"DRIFT", "STEALTH", "CRUISE", "BURN"};

                for (int32_t i = 0; i < 4; ++i)
                {
                    ImGui::SameLine();

                    if (ship.nav.flightMode != flightModes[i])
                    {
                        if (ImGui::Button(flightModes[i]))
                        {
                            Endpoint::Fleet::PatchShipNav(m_Client, m_AgentToken, ship, flightModes[i]);
                            updateShips = true;
                        }
                    }
                    else
                    {
                        ImGui::Text("%s", ship.nav.flightMode.c_str());
                    }
                }

                ImGui::Text("Crew: %i / %i", ship.crew.current, ship.crew.capacity);
                ImGui::Text("Fuel: %i / %i", ship.fuel.current, ship.fuel.capacity);

                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }
    else
    {
        ImGui::Text("Unable to load Ships...");
    }

    if (updateShips)
    {
        updateShips = false;
        ships = Endpoint::Fleet::ListShips(m_Client, m_AgentToken);
    }

    ImGui::End();
}
