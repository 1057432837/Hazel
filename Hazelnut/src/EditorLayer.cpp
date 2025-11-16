#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "EditorLayer.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {
	EditorLayer::EditorLayer() : Layer("EditorLayer") {
		m_CameraController.reset(new OrthographicCameraController(1280.0f / 720.0f, true));

	}

	EditorLayer::~EditorLayer() {

	}

	void EditorLayer::OnAttach() {
		HZ_PROFILE_FUNCTION();

		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");

		m_FbSpec = FramebufferSpecification::Create();

		m_Framebuffer = Framebuffer::Create(*m_FbSpec);

		m_ActiveScene = Scene::Create();

		m_SquareEntity = m_ActiveScene->CreateEntity("Green Square");
		m_SquareEntity->AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		m_CameraEntity->AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
		m_SecondCamera->AddComponent<CameraComponent>().Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			CameraController() {

			}

			~CameraController() {

			}

			void OnCreate() {
				

			}

			void OnDestroy() {

			}

			void OnUpdate(Timestep ts) {
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.0f;

				if (Input::IsKeyPressed(HZ_KEY_A))
				{
					transform[3][0] -= speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_D))
				{
					transform[3][0] += speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_W))
				{
					transform[3][1] += speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_S))
				{
					transform[3][1] -= speed * ts;

				}

			}

		private:

		};

		m_CameraEntity->AddComponent<NativeScriptComponent>().Bind<CameraController>();

	}

	void EditorLayer::OnDetach() {
		HZ_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts) {
		HZ_PROFILE_FUNCTION();

		FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController->OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		
		}
		
		if (m_ViewportFocused)
		{
			m_CameraController->OnUpdate(ts);

		}

		m_Renderer2D->ResetStats();

		{
			HZ_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			m_Renderer = Renderer::Create();
			m_Renderer->Flush({ 0.1f, 0.1f, 0.1f, 1 });

		}

		{
			HZ_PROFILE_SCOPE("Renderer Draw");

			m_ActiveScene->OnUpdate(ts);

			m_Framebuffer->Unbind();

		}

	}

	void EditorLayer::OnImGuiRender() {
		HZ_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;

		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
			window_flags |= ImGuiWindowFlags_NoBackground;

		}

		if (!opt_padding) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		}
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding) {
			ImGui::PopStyleVar();

		}
		if (opt_fullscreen) {
			ImGui::PopStyleVar(2);

		}

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit")) { Application::Get().Close(); }
				ImGui::EndMenu();

			}

			ImGui::EndMenuBar();

		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		if (m_SquareEntity)
		{
			ImGui::Separator();

			auto& tag = m_SquareEntity->GetComponent<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& m_SquareColor = m_SquareEntity->GetComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

			ImGui::Separator();

		}
		
		ImGui::DragFloat3("Camera Transform", glm::value_ptr(m_CameraEntity->GetComponent<TransformComponent>().Transform[3]));

		if (ImGui::Checkbox("Camera Controller", &m_PrimaryCamera))
		{
			m_CameraEntity->GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
			m_SecondCamera->GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
		
		}

		{
			auto& camera = m_SecondCamera->GetComponent<CameraComponent>().Camera;
			float orthoSize = camera.GetOrthographicSize();
			if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize))
			{
				camera.SetOrthographicSize(orthoSize);

			}
			
		}

		ImGui::End();

		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

			m_CameraController->OnResize(viewportPanelSize.x, viewportPanelSize.y);

		}
		
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		ImGui::End();

	}

	void EditorLayer::OnEvent(Event& e) {
		m_CameraController->OnEvent(e);

	}

}