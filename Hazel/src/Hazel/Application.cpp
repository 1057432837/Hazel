#include "hzpch.h"

#include "GLFW/glfw3.h"

#include "Application.h"
#include "Hazel/Log.h"
#include "Input.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() { }

	void Application::Run() {
			while (m_Running) {
				float time = (float)glfwGetTime();
				Timestep timestep = time - m_LastFrameTime;
				m_LastFrameTime = time;

				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);

				}

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();

				}
				m_ImGuiLayer->End();

				m_Window->OnUpdate();

			}

		}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
			m_Running = false;
			return true;

		}

	void Application::OnEvent(Event& e) {
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
			{
				(*--it)->OnEvent(e);
				if (e.Handled)
				{
					break;

				}

			}

		}

	void Application::PushLayer(Layer* layer) {
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();

		}

	void Application::PushOverlay(Layer* layer) {
			m_LayerStack.PushOverlay(layer);
			layer->OnAttach();

		}

}