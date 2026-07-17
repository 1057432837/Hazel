#include "hzpch.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Hazel {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	Renderer::Renderer() {

	}

	Renderer::~Renderer() {

	}

	void Renderer::Init() {
		HZ_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();

	}

	void Renderer::Shutdown() {
		Renderer2D::Shutdown();

	}

	void Renderer::Flush(const glm::vec4& color) {
		RenderCommand::Flush(color);

	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		Cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		Cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		//mi->Bind();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);

	}

	Ref<Renderer> Renderer::Create() {
		return CreateRef<Renderer>();

	}

}