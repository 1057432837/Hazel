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

	void RendererAPI::Flush(const glm::vec4& color) {

	}

	void RendererAPI::SetClearColor(const glm::vec4& color) {

	}

	void RendererAPI::Clear() {

	}

	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {

	}

	void RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

	}

}