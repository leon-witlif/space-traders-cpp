#include <iostream>

#include "GL/gl.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "nlohmann/json.hpp"

#include "HttpClient.h"

int main()
{
    const char* bearerToken = std::getenv("SPACE_TRADERS_TOKEN");
    if (!bearerToken)
    {
        std::cerr << "No bearer token specified. Is the SPACE_TRADERS_TOKEN environment variable set?" << std::endl;
        return -1;
    }

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 720, "SpaceTraders", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        ImGui::Render();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    HttpClient client(bearerToken);
    nlohmann::json response;

    client.MakeRequest("/", response);
    auto status = response.template get<SpaceTraders::Endpoint::Global::GetStatus>();

    std::cout << "Status: " << status.status << std::endl 
        << "Version: " << status.version << std::endl
        << "ResetDate: " << status.resetDate << std::endl
        << "Description: " << status.description << std::endl << std::endl;

    client.MakeRequest("/agents", response);
    auto agents = response.template get<SpaceTraders::Endpoint::Agent::ListAgents>();

    std::cout << "Count agents: " << agents.data.size() << std::endl << std::endl;

    for (int32_t i = 0; i < 3; ++i)
    {
        std::cout << "AccountId: " << agents.data[i].accountId.value_or("Unknown") << std::endl
            << "Symbol: " << agents.data[i].symbol << std::endl
            << "Headquarters: " << agents.data[i].headquarters << std::endl
            << "Credits: " << agents.data[i].credits << std::endl
            << "StartingFaction" << agents.data[i].startingFaction << std::endl
            << "ShipCount: " << agents.data[i].shipCount << std::endl << std::endl;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
