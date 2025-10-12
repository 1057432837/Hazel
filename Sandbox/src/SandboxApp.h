#pragma once

#include "Hazel.h"

namespace Hazel {
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer();

		virtual ~ExampleLayer();

		void OnUpdate(Timestep ts) override;

		virtual void OnImGuiRender() override;

		void OnEvent(Event& e) override;

	private:
		Ref<BufferLayout> m_Layout;

		Ref<VertexArray> m_VertexArray;

		Ref<VertexBuffer> m_VertexBuffer;

		Ref<IndexBuffer> m_IndexBuffer;

		Ref<Shader> m_Shader;

		Ref<BufferLayout> m_SquareVBLayout;

		Ref<VertexArray> m_SquareVA;

		Ref<VertexBuffer> m_SquareVB;

		Ref<IndexBuffer> m_SquareIB;

		Ref<Shader> m_FlatColorShader;

		Ref<Texture2D> m_Texture;

		Ref<Shader> m_TextureShader;

		Ref<OrthographicCameraController> m_CameraController;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	};

	class Sandbox : public Application
	{
	public:
		Sandbox();

		~Sandbox();

	private:

	};

}