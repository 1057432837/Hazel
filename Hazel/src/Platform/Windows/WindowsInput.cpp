#include "hzpch.h"
#include "GLFW/glfw3.h"

#include "WindowsInput.h"
#include "Hazel/Core/Application.h"

namespace Hazel {
	Input* Input::s_Instance = Create();

	WindowsInput::WindowsInput() {

	}

	WindowsInput::~WindowsInput() {

	}

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;

	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;

	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };

	}

	float WindowsInput::GetMouseXImpl() {
		//auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);
		auto[x, y] = GetMousePositionImpl();

		return x;

	}

	float WindowsInput::GetMouseYImpl() {
		auto [x, y] = GetMousePositionImpl();

		return y;

	}

	Input* Input::Create() {
		return new WindowsInput();

	}

}