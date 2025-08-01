#include "hzpch.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "GL/GL.h"

#include "Hazel/Core/Core.h"
#include "OpenGLContext.h"

namespace Hazel {
	OpenGLContext::OpenGLContext() {

	}

	OpenGLContext::~OpenGLContext() {

	}

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
		Init();

	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("  Vender: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef HZ_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			HZ_CORE_ASSERT(versionMajor > 4 || versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5";

		#endif

	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);

	}

	GraphicsContext* GraphicsContext::Create(GLFWwindow* windowHandle) {
		return new OpenGLContext(windowHandle);

	}

}