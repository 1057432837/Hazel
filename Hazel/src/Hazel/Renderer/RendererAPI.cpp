#include "hzpch.h"

#include "RendererAPI.h"

namespace Hazel {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI::RendererAPI() {

	}

	RendererAPI::~RendererAPI() {

	}

	void RendererAPI::SetClearColor(const glm::vec4& color) {

	}

	void RendererAPI::Clear() {

	}

	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray) {

	}

}