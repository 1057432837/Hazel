#pragma once

#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();

	virtual ~Sandbox2D();

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	void OnEvent(Hazel::Event& e) override;

private:
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::VertexBuffer> m_SquareVB;

	Hazel::Ref<Hazel::IndexBuffer> m_SquareIB;

	Hazel::Ref<Hazel::BufferLayout> m_SquareVBLayout;

	Hazel::Ref<Hazel::OrthographicCameraController> m_CameraController;

	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

};