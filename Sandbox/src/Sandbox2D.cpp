#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

#define PROFILE_SCOPE(name) Hazel::Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") {
	m_CameraController.reset(new Hazel::OrthographicCameraController(1280.0f / 720.0f, true));

}

Sandbox2D::~Sandbox2D() {

}

void Sandbox2D::OnAttach() {
	HZ_PROFILE_FUNCTION();

	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/avatar.jpg");

}

void Sandbox2D::OnDetach() {
	HZ_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
	HZ_PROFILE_FUNCTION();

	m_CameraController->OnUpdate(ts);
	
	{
		HZ_PROFILE_SCOPE("Renderer Prep");
		Hazel::Renderer::Flush({ 0.1f, 0.1f, 0.1f, 1 });

	}
	
	{
		HZ_PROFILE_SCOPE("Renderer Draw");
		m_Renderer2D = Hazel::Renderer2D::Create();

		m_Renderer2D->BeginScene(m_CameraController->GetCamera());

		m_Renderer2D->DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		m_Renderer2D->DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		m_Renderer2D->DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);

		m_Renderer2D->EndScene();

	}
	
}

void Sandbox2D::OnImGuiRender() {
	HZ_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

}

void Sandbox2D::OnEvent(Hazel::Event& e) {
	m_CameraController->OnEvent(e);

}