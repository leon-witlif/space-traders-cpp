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

#include "Model.h"

namespace SpaceTraders
{
    class Window
    {
        public:
            Window(const Model::Global::Status* status, const Model::Agent::Agent* agent, const std::vector<Model::Fleet::Ship>* ships, const std::vector<Model::Contract::Contract>* contracts);
            ~Window();

            void RunWindowLoop();

        private:
            void ShowGlobalWindow();
            void ShowAgentWindow();
            void ShowContractWindow();
            void ShowShipWindow();

        private:
            GLFWwindow* m_Window;

            const Model::Global::Status* m_Status;
            const Model::Agent::Agent* m_Agent;
            const std::vector<Model::Fleet::Ship>* m_Ships;
            const std::vector<Model::Contract::Contract>* m_Contracts;
    };
}

#endif
