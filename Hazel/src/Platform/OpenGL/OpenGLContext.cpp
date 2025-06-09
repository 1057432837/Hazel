#include "hzpch.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "GL/GL.h"

#include "Hazel/Core.h"
#include "Hazel/Log.h"
#include "OpenGLContext.h"

namespace Hazel {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	OpenGLContext::~OpenGLContext() {

	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("  Vender: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);

	}

}