#include "hzpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {
	Shader::Shader() {

	}

	Shader::~Shader() {

	}

	void Shader::Bind() const {

	}

	void Shader::Unbind() const {

	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return new OpenGLShader(vertexSrc, fragmentSrc);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}