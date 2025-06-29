#include "hzpch.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::BeginScene(OrthoGraphicCamera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		//mi->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}