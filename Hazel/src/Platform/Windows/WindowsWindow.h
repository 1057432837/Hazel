#pragma once

#include "GLFW/glfw3.h"

#include "Hazel/Log.h"
#include "Hazel/Window.h"

struct GLFWwindow;

namespace Hazel {
	class WindowsWindow : public Window
	{
	public:
		inline unsigned int GetWidth() const override;

		inline unsigned int GetHeight() const override;

		bool IsVSync() const override;

		void OnUpdate() override;

		void SetVSync(bool enabled) override;

		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		inline virtual void* GetNativeWindow() const { return m_Window; };

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		}m_Data;

		GLFWwindow* m_Window;

		virtual void Init(const WindowProps& props);

		virtual void Shutdown();
	};

}