#pragma once

#include "Event.h"

namespace Hazel {
	class HAZEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent() = default;

		~MouseMovedEvent() = default;

		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) { }

		inline float GetX() const { return m_MouseX; }

		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ',' << m_MouseY;
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseMoved)

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;

	};

	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent() = default;

		~MouseScrolledEvent() = default;

		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) { }

		inline float GetXOffset() const { return m_XOffset; }

		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ',' << GetYOffset();
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseScrolled)

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;

	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent() = default;

		~MouseButtonEvent() = default;

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		int m_Button;

		MouseButtonEvent(int button) : m_Button(button){ }

	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent() = default;

		~MouseButtonPressedEvent() = default;

		MouseButtonPressedEvent(int button) : MouseButtonEvent(button){ }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	private:

	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent() = default;

		~MouseButtonReleasedEvent() = default;

		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) { }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();

		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	private:

	};

}