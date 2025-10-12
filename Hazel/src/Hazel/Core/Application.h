#pragma once

#include "Core.h"
#include "Hazel/Events/Event.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"	
#include "Hazel/Core/TimeStep.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
	class Application
	{
	public:
		Application();

		virtual ~Application();

		Application(const std::string& name = "Hazel App");

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; };

		inline Window& GetWindow() { return *m_Window; };

		void Close();

	private:
		Scope<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		bool m_Minimized = false;

		bool OnWindowMoved(WindowMovedEvent& e);

		bool OnWindowClose(WindowCloseEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

		float m_LastFrameTime = 0.0f;

	};

	Application* CreateApplication();

}
