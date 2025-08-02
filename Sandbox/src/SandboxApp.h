#pragma once

#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer();

	virtual ~ExampleLayer();

	void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	void OnEvent(Hazel::Event& e) override;

private:
	Hazel::Ref<Hazel::BufferLayout> m_Layout;

	Hazel::Ref<Hazel::VertexArray> m_VertexArray;

	Hazel::Ref<Hazel::VertexBuffer> m_VertexBuffer;

	Hazel::Ref<Hazel::IndexBuffer> m_IndexBuffer;

	Hazel::Ref<Hazel::Shader> m_Shader;

	Hazel::Ref<Hazel::BufferLayout> m_SquareVBLayout;

	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::VertexBuffer> m_SquareVB;

	Hazel::Ref<Hazel::IndexBuffer> m_SquareIB;

	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

	Hazel::Ref<Hazel::Texture2D> m_Texture;

	Hazel::Ref<Hazel::Shader> m_TextureShader;

	Hazel::Ref<Hazel::OrthographicCameraController> m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Hazel::Application
{
public:
	Sandbox();

	~Sandbox();

private:

};
