#pragma once

#include "RenderCommand.h"
#include "OrthoGraphicCamera.h"
#include "Shader.h"

namespace Hazel {
	class Renderer
	{
	public:
		Renderer();

		~Renderer();

		static void Init();

		static void Flush(const glm::vec4& color);

		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static void OnWindowResize(uint32_t width, uint32_t height);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

		};

		static SceneData* m_SceneData;

	};

}