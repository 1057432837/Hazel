#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"	

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* layer);

		inline static Application& Get();

		inline Window& GetWindow();

	private:
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}
