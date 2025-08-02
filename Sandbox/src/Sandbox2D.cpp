#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") {
	m_CameraController.reset(new Hazel::OrthographicCameraController(1280.0f / 720.0f, true));

}

Sandbox2D::~Sandbox2D() {

}

void Sandbox2D::OnAttach() {
	/*--------------------------------------------------------------------------------------------------------------*/
	float squareVertices[3 * 4] = {																					//
		-0.5f, -0.5f,  0.0f,																						//
		 0.5f, -0.5f,  0.0f,																						//
		 0.5f,  0.5f,  0.0f,																						//
		-0.5f,  0.5f,  0.0f,																						//
																													//
	};																												//
																													//
	m_SquareVBLayout = Hazel::BufferLayout::Create({																//
		{ Hazel::ShaderDataType::Float3, "a_Position" },															//
																													//
	});																												//
																													//
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };																//
																													//
	m_SquareVA = Hazel::VertexArray::Create();																		//
	m_SquareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));								//
	m_SquareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));				//
	m_FlatColorShader = Hazel::Shader::Create("assets/shaders/FlatColor.glsl");										//
																													//
	m_SquareVB->SetLayout(m_SquareVBLayout);																		//
	m_SquareVA->SetIndexBuffer(m_SquareIB);																			//
	m_SquareVA->AddVertexBuffer(m_SquareVB);																		//
																													//
	/*--------------------------------------------------------------------------------------------------------------*/
	m_CameraController.reset(new Hazel::OrthographicCameraController(1280.0f / 720.0f, true));

}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController->OnUpdate(ts);

	Hazel::Renderer::Flush({ 0.1f, 0.1f, 0.1f, 1 });

	Hazel::Renderer::BeginScene(m_CameraController->GetCamera());

	Hazel::Cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
	Hazel::Cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazel::Renderer::EndScene();

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController->OnEvent(e);

}