#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"	
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

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

		inline static Application& Get() { return *s_Instance; };

		inline Window& GetWindow() { return *m_Window; };

	private:
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent& e);

		LayerStack m_LayerStack;

		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;

		std::shared_ptr<VertexArray> m_SquareVA;

	};

	Application* CreateApplication();

}
