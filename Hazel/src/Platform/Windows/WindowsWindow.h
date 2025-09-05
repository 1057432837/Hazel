#pragma once

#include "GLFW/glfw3.h"

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();

		virtual ~WindowsWindow();

		WindowsWindow(const WindowProps& props);

		void OnUpdate() override;

		inline void SetPosition(unsigned int xPos, unsigned int yPos) const { glfwSetWindowPos(m_Window, xPos, yPos); }

		inline unsigned int GetWidth() const { return m_Data.Width; }

		inline unsigned int GetHeight() const { return m_Data.Height; }

		bool IsVSync() const { return m_Data.VSync; }

		void SetVSync(bool enabled) {
			HZ_PROFILE_FUNCTION();
			
			if (enabled)
			{
				glfwSwapInterval(1);

			}
			else
			{
				glfwSwapInterval(0);

			}
			m_Data.VSync = enabled;

		}

		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			unsigned int XPos, YPos;
			bool IsFocused;
			bool VSync;

			EventCallbackFn EventCallback;
		}m_Data;

		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		virtual void Init(const WindowProps& props);

		virtual void Shutdown();

	};

}