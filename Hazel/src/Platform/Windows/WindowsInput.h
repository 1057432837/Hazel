#pragma once

#include "Hazel/Input.h"

namespace Hazel {
	class WindowsInput : public Input
	{
	public:
		WindowsInput();

		~WindowsInput();

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;

		virtual std::pair<float, float> GetMousePositionImpl() override;

		virtual float GetMouseXImpl() override;

		virtual float GetMouseYImpl() override;

	private:

	};

}