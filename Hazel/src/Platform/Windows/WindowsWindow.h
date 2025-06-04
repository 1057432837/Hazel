#pragma once

#include "GLFW/glfw3.h"

#include "Hazel/Log.h"
#include "Hazel/Window.h"

struct GLFWwindow;

namespace Hazel {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override;

		inline unsigned int GetHeight() const override;

		bool IsVSync() const override;

		void SetVSync(bool enabled) override;

		inline void SetEventCallback(const EventCallbackFn& callback) override;

		inline virtual void* GetNativeWindow() const;

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