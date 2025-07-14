#pragma once

#include "Event.h"

namespace Hazel {
	class HAZEL_API KeyEvent : public Event
	{
	public:
		KeyEvent() = default;

		~KeyEvent() = default;

		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		int m_KeyCode;

		KeyEvent(int keycode) : m_KeyCode(keycode) { }

	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent() = default;

		~KeyPressedEvent() = default;

		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
			return ss.str();

		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;

	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent() = default;

		~KeyReleasedEvent() = default;

		KeyReleasedEvent(int keycode) : KeyEvent(keycode){ };

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();

		}

		EVENT_CLASS_TYPE(KeyReleased)

	private:

	};

	class HAZEL_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent() = default;

		~KeyTypedEvent() = default;

		KeyTypedEvent(int keycode) : KeyEvent(keycode) { }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	private:

	};

}