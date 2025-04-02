#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <iostream>
#include <vector>

#include "GL/gl.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "HttpClient.h"
#include "Endpoint.h"

namespace SpaceTraders
{
    class Window
    {
        public:
            Window(HttpClient& client, const std::string& agentToken);
            ~Window();

            void RunWindowLoop();

        private:
            void ShowGlobalWindow();
            void ShowAgentWindow();
            void ShowContractWindow();
            void ShowShipWindow();

        private:
            HttpClient& m_Client;
            const std::string& m_AgentToken;

            GLFWwindow* m_Window;
    };
}

#endif
