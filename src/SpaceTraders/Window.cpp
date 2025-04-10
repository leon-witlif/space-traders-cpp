#include "Window.h"

static std::chrono::time_point<std::chrono::system_clock> last, current;

static bool updateAgent = false;
static bool updateContracts = false;
static bool updateShips = false;

static ImGuiWindowFlags DefaultWindowFlags = ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoBringToFrontOnFocus;

SpaceTraders::Window::Window(HttpClient& client, Config& config)
    : m_Client(client), m_Config(config)
{
    m_Status = std::make_unique<std::optional<Model::Global::Status>>(Endpoint::Global::GetStatus(m_Client));

    m_ShouldUpdate = true;
    m_UpdateThread = new std::thread([this]() { UpdateLoop(); });

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
    m_ShouldUpdate = false;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();

    m_UpdateThread->join();
    delete m_UpdateThread;
}

void SpaceTraders::Window::UpdateLoop()
{
    while (m_ShouldUpdate)
    {
        current = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::seconds>(current - last);

        if (diff >= std::chrono::seconds(15))
        {
            last = current;

            updateAgent = updateContracts = updateShips = true;
            UpdateData();
        }
    }
}

void SpaceTraders::Window::UpdateData()
{
    std::lock_guard<std::mutex> lock(m_DataMutex);

    if (updateAgent)
    {
        updateAgent = false;
        m_Agent = std::make_unique<std::optional<Model::Agent::Agent>>(Endpoint::Agent::GetAgent(m_Client, m_Config.GetAgentToken()));
    }

    if (updateContracts)
    {
        updateContracts = false;
        m_Contracts = std::make_unique<std::vector<Model::Contract::Contract>>(Endpoint::Contract::ListContracts(m_Client, m_Config.GetAgentToken()).first);
    }

    if (updateShips)
    {
        updateShips = false;
        m_Ships = std::make_unique<std::vector<Model::Fleet::Ship>>(Endpoint::Fleet::ListShips(m_Client, m_Config.GetAgentToken()).first);
    }
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

    ImGui::Begin("Global", nullptr, DefaultWindowFlags);

    if (m_Status && *m_Status)
    {
        std::lock_guard<std::mutex> lock(m_DataMutex);

        ImGui::Text("Status: %s", (*m_Status)->status.c_str());
        ImGui::Text("Version: %s", (*m_Status)->version.c_str());
        ImGui::Text("ResetDate: %s", (*m_Status)->resetDate.c_str());
        ImGui::TextWrapped("Description: %s", (*m_Status)->description.c_str());
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

    ImGui::Begin("Agent", nullptr, DefaultWindowFlags);

    if (m_Agent && *m_Agent)
    {
        std::lock_guard<std::mutex> lock(m_DataMutex);

        ImGui::Text("Symbol: %s", (*m_Agent)->symbol.c_str());
        ImGui::Text("Headquarters: %s", (*m_Agent)->headquarters.c_str());
        ImGui::Text("Credits: %li", (*m_Agent)->credits);
        ImGui::Text("StartingFaction: %s", (*m_Agent)->startingFaction.c_str());
        ImGui::Text("ShipCount: %i", (*m_Agent)->shipCount);
    }
    else
    {
        ImGui::Text("Unable to load Agent...");
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowContractWindow()
{
    ImGui::SetNextWindowPos(ImVec2(0, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    ImGui::Begin("Contract", nullptr, DefaultWindowFlags);

    if (m_Contracts && (*m_Contracts).size())
    {
        std::lock_guard<std::mutex> lock(m_DataMutex);

        ImGui::BeginTabBar("Contracts");

        for (const auto& contract : *m_Contracts)
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
                        Endpoint::Contract::AcceptContract(m_Client, m_Config.GetAgentToken(), contract);
                        /*m_Config.GetConfig()["contracts"] = {
                            { { "id", contract.id }, { "accepted", true } }
                        };*/
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
        UpdateData();
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowShipWindow()
{
    ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    ImGui::Begin("Ship", nullptr, DefaultWindowFlags);

    if (m_Ships && (*m_Ships).size())
    {
        std::lock_guard<std::mutex> lock(m_DataMutex);

        ImGui::BeginTabBar("Ships");

        for (const auto& ship : *m_Ships)
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
                            Endpoint::Fleet::PatchShipNav(m_Client, m_Config.GetAgentToken(), ship, flightModes[i]);
                            updateShips = true;
                        }
                    }
                    else
                    {
                        ImGui::Text("%s", ship.nav.flightMode.c_str());
                    }
                }

                ImGui::Text("Crew: %i / %i", ship.crew.current, ship.crew.capacity);

                if (ship.cooldown.remainingSeconds)
                {
                    ImGui::Text("Cooldown: %i seconds", ship.cooldown.remainingSeconds);
                }

                ImGui::AlignTextToFramePadding();
                ImGui::Text("Fuel: %i / %i", ship.fuel.current, ship.fuel.capacity);
                ImGui::SameLine();
                if (ImGui::Button("Refuel"))
                {
                    std::cout << "Refuel" << std::endl;
                }

                if (ImGui::Button("Negotiate Contract"))
                {
                    Endpoint::Fleet::NegotiateContract(m_Client, m_Config.GetAgentToken(), ship);
                    updateShips = updateContracts = true;
                }

                ImGui::SameLine();
                if (ImGui::Button("Create Chart"))
                {
                    Endpoint::Fleet::CreateChart(m_Client, m_Config.GetAgentToken(), ship);
                    updateShips = true;
                }

                ImGui::SameLine();
                if (ImGui::Button("Create Survey"))
                {
                    Endpoint::Fleet::OrbitShip(m_Client, m_Config.GetAgentToken(), ship);
                    Endpoint::Fleet::CreateSurvey(m_Client, m_Config.GetAgentToken(), ship);
                    Endpoint::Fleet::DockShip(m_Client, m_Config.GetAgentToken(), ship);
                    updateShips = true;
                }

                ImGui::AlignTextToFramePadding();
                ImGui::Text("Navigate to:");
                ImGui::SameLine();
                static char destinationSymbol[16] = "";
                ImGui::SetNextItemWidth(128.f);
                ImGui::InputText("##destinationSymbol", destinationSymbol, sizeof(destinationSymbol), ImGuiInputTextFlags_CharsUppercase);
                ImGui::SameLine();
                if (ImGui::Button("Go!"))
                {
                    Endpoint::Fleet::OrbitShip(m_Client, m_Config.GetAgentToken(), ship);
                    Endpoint::Fleet::NavigateShip(m_Client, m_Config.GetAgentToken(), ship, destinationSymbol);
                    updateShips = true;
                }

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
        UpdateData();
    }

    ImGui::End();
}
