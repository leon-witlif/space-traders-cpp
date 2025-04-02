#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
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
            void UpdateLoop();
            void UpdateData();

            void ShowGlobalWindow();
            void ShowAgentWindow();
            void ShowContractWindow();
            void ShowShipWindow();

        private:
            HttpClient& m_Client;
            const std::string& m_AgentToken;

            GLFWwindow* m_Window;

            std::thread* m_UpdateThread;
            std::atomic<bool> m_ShouldUpdate;
            std::mutex m_DataMutex;

            std::unique_ptr<std::optional<Model::Global::Status>> m_Status;
            std::unique_ptr<std::optional<Model::Agent::Agent>> m_Agent;
            std::unique_ptr<std::vector<Model::Contract::Contract>> m_Contracts;
            std::unique_ptr<std::vector<Model::Fleet::Ship>> m_Ships;
    };
}

#endif
