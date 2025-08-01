#include "hzpch.h"

#include "GLFW/glfw3.h"

#include "Application.h"
#include "Input.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if (!monitor)
		{
			return;

		}

		int monitorX, monitorY, monitorW, monitorH;
		glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorW, &monitorH);

		unsigned int windowX = monitorW / 2 - m_Window->GetWidth() / 2;
		unsigned int windowY = monitorH / 2 - m_Window->GetHeight() / 2;

		std::ifstream ifs("WindowConfig.cfg");
		if (ifs.is_open())
		{
			std::string line;
			if (std::getline(ifs, line)) {
				std::istringstream iss(line);
				iss >> windowX >> windowY;

			}

			ifs.close();

		}

		m_Window->SetPosition(windowX, windowY);

		Renderer::Init();

		m_ImGuiLayer = static_cast<ImGuiLayer*>(Layer::Create());
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);

				}

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

	bool Application::OnWindowMoved(WindowMovedEvent& e) {
		std::ofstream ofs("WindowConfig.cfg");
		if (ofs.is_open()) {
			ofs << e.GetXPos() << " " << e.GetYPos() << std::endl;
			ofs.close();

		}

		return false;

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;

	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;

		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowMovedEvent>(BIND_EVENT_FN(OnWindowMoved));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

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