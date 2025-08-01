#pragma once

#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine", unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height) { }
	};

	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual void SetPosition(unsigned int xPos, unsigned int yPos) const = 0;

		virtual unsigned int GetWidth() const = 0;

		virtual unsigned int GetHeight() const = 0;

		virtual bool IsVSync() const = 0;

		virtual void SetVSync(bool enabled) = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() const = 0;
		
		static Scope<Window> Create(const WindowProps& props = WindowProps());

	private:

	};

}