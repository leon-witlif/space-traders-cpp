#include "Window.h"

static ImGuiWindowFlags DefaultWindowFlags = ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_NoMove
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoBringToFrontOnFocus;

SpaceTraders::Window::Window(const Model::Global::Status* status, const Model::Agent::Agent* agent, const std::vector<Model::Fleet::Ship>* ships, const std::vector<Model::Contract::Contract>* contracts)
    : m_Status(status), m_Agent(agent), m_Ships(ships), m_Contracts(contracts)
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
    // io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf", 14);

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

    ImGui::Begin("Global", nullptr, DefaultWindowFlags);

    if (m_Status)
    {
        ImGui::Text("Status: %s", m_Status->status.c_str());
        ImGui::Text("Version: %s", m_Status->version.c_str());
        ImGui::Text("ResetDate: %s", m_Status->resetDate.c_str());
        ImGui::TextWrapped("Description: %s", m_Status->description.c_str());
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowAgentWindow()
{
    ImGui::SetNextWindowPos(ImVec2(640, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    ImGui::Begin("Agent", nullptr, DefaultWindowFlags);

    if (m_Agent && m_Agent->symbol.length())
    {
        ImGui::Text("Symbol: %s", m_Agent->symbol.c_str());
        ImGui::Text("Headquarters: %s", m_Agent->headquarters.c_str());
        ImGui::Text("Credits: %li", m_Agent->credits);
        ImGui::Text("StartingFaction: %s", m_Agent->startingFaction.c_str());
        ImGui::Text("ShipCount: %i", m_Agent->shipCount);
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowContractWindow()
{
    ImGui::SetNextWindowPos(ImVec2(0, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    ImGui::Begin("Contract", nullptr, DefaultWindowFlags);

    if (m_Contracts && m_Contracts->size())
    {
        ImGui::BeginTabBar("Contracts");

        for (const auto& contract: *m_Contracts)
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
                ImGui::Text("DeadlineToAccept: %s", contract.deadlineToAccept.c_str());

                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void SpaceTraders::Window::ShowShipWindow()
{
    ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_Always);

    ImGui::Begin("Ship", nullptr, DefaultWindowFlags);

    if (m_Ships && m_Ships->size())
    {
        ImGui::BeginTabBar("Ships");

        for (const auto& ship : *m_Ships)
        {
            if (ImGui::BeginTabItem(ship.symbol.c_str()))
            {
                ImGui::Text("Role: %s", ship.registration.role.c_str());
                ImGui::Text("Crew: %i / %i", ship.crew.current, ship.crew.capacity);
                ImGui::Text("Fuel: %i / %i", ship.fuel.current, ship.fuel.capacity);

                ImGui::EndTabItem();
            }
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
