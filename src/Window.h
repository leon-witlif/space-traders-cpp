#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <iostream>

#include "GL/gl.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Endpoint.h"

namespace SpaceTraders
{
    class Window
    {
        public:
            Window(const Endpoint::Global::GetStatus* status, const Endpoint::Agent::GetAgent* agent, const Endpoint::Fleet::ListShips* ships);
            ~Window();

            void RunWindowLoop();

        private:
            void ShowGlobalWindow();
            void ShowAgentWindow();
            void ShowContractWindow();
            void ShowShipWindow();

        private:
            GLFWwindow* m_Window;

            const Endpoint::Global::GetStatus* m_Status;
            const Endpoint::Agent::GetAgent* m_Agent;
            const Endpoint::Fleet::ListShips* m_Ships;
    };
}

#endif
