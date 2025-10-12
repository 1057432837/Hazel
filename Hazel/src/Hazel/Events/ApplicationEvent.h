#pragma once

#include "Event.h"

namespace Hazel {
	class HAZEL_API WindowMovedEvent : public Event {
	public:
		WindowMovedEvent() = default;

		~WindowMovedEvent() = default;

		WindowMovedEvent(unsigned int XPos, unsigned int YPos) : m_XPos(XPos), m_YPos(YPos) { }

		inline unsigned int GetXPos() const { return m_XPos; }

		inline unsigned int GetYPos() const { return m_YPos; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowMovedEvent: " << m_XPos << ',' << m_YPos;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowMoved)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_XPos, m_YPos;

	};

	class HAZEL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent() = default;

		~WindowResizeEvent() = default;

		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) { }

		inline unsigned int GetWidth() const { return m_Width; }

		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ',' << m_Height;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowResize)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;

	};

	class HAZEL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		~WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};

	class HAZEL_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		~WindowFocusEvent() = default;

		WindowFocusEvent(bool focused) { }

		inline bool GetFocused() const { return m_Focused; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowFocusEvent: " << m_Focused;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowFocus)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		bool m_Focused;

	};

	class HAZEL_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		~WindowLostFocusEvent() = default;

		WindowLostFocusEvent(bool focused) { }

		inline bool GetFocused() const { return m_Focused; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Focused;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowLostFocus)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		bool m_Focused;

	};

	class HAZEL_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		~AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};

	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		~AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};
	
	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		~AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)

		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:

	};

}