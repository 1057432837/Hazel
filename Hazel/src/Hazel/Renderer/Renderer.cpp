#include "hzpch.h"

#include "Renderer.h"

namespace Hazel {
	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::BeginScene() {

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}