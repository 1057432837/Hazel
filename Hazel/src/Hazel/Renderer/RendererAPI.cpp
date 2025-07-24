#include "hzpch.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI::RendererAPI() {

	}

	RendererAPI::~RendererAPI() {

	}

	void RendererAPI::Init() {

	}

	void RendererAPI::SetClearColor(const glm::vec4& color) {

	}

	void RendererAPI::Clear() {

	}

	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {

	}

	void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

	}

	static RendererAPI* Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return new OpenGLRendererAPI;

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}