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

}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	m_CameraController->OnUpdate(ts);

	Hazel::Renderer::Flush({ 0.1f, 0.1f, 0.1f, 1 });

	Hazel::Renderer2D::BeginScene(m_CameraController->GetCamera());

	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	Hazel::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController->OnEvent(e);

}