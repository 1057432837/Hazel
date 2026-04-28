#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ImGuizmo.h"

#include "EditorLayer.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Scene/SceneSerializer.h"
#include "Hazel/Utils/PlatformUtils.h"
#include "Hazel/Math/Math.h"

namespace Hazel {
	const std::filesystem::path g_AssetPath;

	EditorLayer::EditorLayer() : Layer("EditorLayer") {
		m_CameraController.reset(new OrthographicCameraController(1280.0f / 720.0f, true));

	}

	EditorLayer::~EditorLayer() {

	}

	void EditorLayer::OnAttach() {
		HZ_PROFILE_FUNCTION();

		m_CheckerboardTexture = Texture2D::Create("assets/textures/Checkerboard.png");

		m_FbSpec = FramebufferSpecification::Create();
		m_FbSpec->Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		m_FbSpec->Width = 1280;
		m_FbSpec->Height = 720;
		m_Framebuffer = Framebuffer::Create(*m_FbSpec);

		m_ActiveScene = Scene::Create();

		m_EditorCamera = CreateRef<EditorCamera>(30.0f, 1.0f, 0.1f, 1000.0f);

		m_ContentBrowserPanel = ContentBrowserPanel::Create();

#if 0
		auto greenSquare = m_ActiveScene->CreateEntity("Green Square");
		greenSquare->AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		auto redSquare = m_ActiveScene->CreateEntity("Red Square");
		redSquare->AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
		m_CameraEntity->AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
		m_SecondCamera->AddComponent<CameraComponent>().Primary = false;

		class CameraController : public ScriptableEntity
		{
		public:
			CameraController() {

			}

			~CameraController() {

			}

			void OnCreate() {
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;

			}

			void OnDestroy() {

			}

			void OnUpdate(Timestep ts) {
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(HZ_KEY_A))
				{
					translation.x -= speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_D))
				{
					translation.x += speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_W))
				{
					translation.y += speed * ts;

				}
				if (Input::IsKeyPressed(HZ_KEY_S))
				{
					translation.y -= speed * ts;

				}

			}

		private:

		};

		m_CameraEntity->AddComponent<NativeScriptComponent>().Bind<CameraController>();
		m_SecondCamera->AddComponent<NativeScriptComponent>().Bind<CameraController>();

#endif

		m_SceneHierarchyPanel = SceneHierarchyPanel::Create();
		m_SceneHierarchyPanel->SetContext(m_ActiveScene);

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
			m_EditorCamera->SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		
		}
		
		if (m_ViewportFocused)
		{
			m_CameraController->OnUpdate(ts);

		}

		m_EditorCamera->OnUpdate(ts);

		m_Renderer2D->ResetStats();

		{
			HZ_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			m_Renderer = Renderer::Create();
			m_Renderer->Flush({ 0.1f, 0.1f, 0.1f, 1 });

		}

		{
			HZ_PROFILE_SCOPE("Renderer Draw");

			m_Framebuffer->ClearAttachment(1, -1);

			m_ActiveScene->OnUpdateEditor(ts, *m_EditorCamera);

			auto [mx, my] = ImGui::GetMousePos();
			mx -= m_ViewportBounds[0].x;
			my -= m_ViewportBounds[0].y;
			glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
			my = viewportSize.y - my;
			int mouseX = (int)mx;
			int mouseY = (int)my;

			if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
			{
				int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
				HZ_CORE_WARN("Pixel Data = {0}", pixelData);
				m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, m_ActiveScene.get());

			}

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
		ImGuiStyle& style = ImGui::GetStyle();
		float minWindowSize = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

		}

		style.WindowMinSize.x = minWindowSize;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N")) {
					NewScene();

				}

				if (ImGui::MenuItem("Open...", "Ctrl+O")) {
					OpenScene();

				}

				if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S")) {
					SaveSceneAs();
					
				}

				if (ImGui::MenuItem("Exit")) {
					Application::Get().Close(); 
				
				}

				ImGui::EndMenu();

			}

			ImGui::EndMenuBar();

		}

		m_SceneHierarchyPanel->OnImGuiRender();
		
		m_ContentBrowserPanel->OnImGuiRender();

		ImGui::Begin("Stats");

		std::string name = "None";
		if (m_HoveredEntity)
		{
			name = m_HoveredEntity.GetComponent<TagComponent>().Tag;

		}

		ImGui::Text("Hovered Entity: %s", name.c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMax();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMin();
		auto viewportOffset = ImGui::GetWindowPos();
		m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

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

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* path = (const wchar_t*)payload->Data;
				OpenScene(std::filesystem::path(g_AssetPath) / path);

			}
			
			ImGui::EndDragDropTarget();

		}

		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		Entity selectedEntity = m_SceneHierarchyPanel->GetSelectedEntity();
		if (selectedEntity && m_GizmoType != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = ImGui::GetWindowWidth();
			float windowHeight = ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			//auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			//const glm::mat4& cameraProjection = camera.GetProjection();
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			const glm::mat4& cameraProjection = m_EditorCamera->GetProjection();
			glm::mat4 cameraView = m_EditorCamera->GetViewMatrix();

			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();
			
			bool snap = Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL);
			float snapValue = 0.5f;
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
			{
				snapValue = 45.0f;

			}

			float snapValues[3] = { snapValue, snapValue, snapValue };
			
			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;

			}

		}
		
		ImGui::End();

		ImGui::End();

	}

	void EditorLayer::OnEvent(Event& e) {
		m_CameraController->OnEvent(e);
		m_EditorCamera->OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));

	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		if (e.GetRepeatCount() > 0) {
			return false;

		}

		bool control = Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL) || Input::IsKeyPressed(HZ_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT) || Input::IsKeyPressed(HZ_KEY_RIGHT_SHIFT);
		switch (e.GetKeyCode())
		{
		case HZ_KEY_N: {
			if (control)
			{
				NewScene();

			}
			break;

		}

		case HZ_KEY_O: {
			if (control)
			{
				OpenScene();

			}
			break;

		}

		case HZ_KEY_S: {
			if (control && shift)
			{
				SaveSceneAs();

			}
			break;

		}

		case HZ_KEY_Q: {
			m_GizmoType = -1;
			break;

		}

		case HZ_KEY_W: {
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;

		}

		case HZ_KEY_E: {
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;

		}

		case HZ_KEY_R: {
			m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;

		}

		}

	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == HZ_MOUSE_BUTTON_LEFT)
		{
			if (m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(HZ_KEY_LEFT_ALT))
			{
				m_SceneHierarchyPanel->SetSelectedEntity(m_HoveredEntity);

			}
			
		}

		return false;

	}

	void EditorLayer::NewScene() {
		m_ActiveScene = Scene::Create();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel->SetContext(m_ActiveScene);

	}

	void EditorLayer::OpenScene() {
		std::string filepath = FileDialogs::OpenFile("Hazel Scene (*.hazel)\0*.hazel\0");
		if (!filepath.empty())
		{
			OpenScene(filepath);

		}

	}

	void EditorLayer::OpenScene(const std::filesystem::path& path) {
		m_ActiveScene = Scene::Create();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel->SetContext(m_ActiveScene);

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(path.string());

	}

	void EditorLayer::SaveSceneAs() {
		std::string filepath = FileDialogs::SaveFile("Hazel Scene (*.hazel)\0*.hazel\0");
		if (!filepath.empty()) {
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);

		}

	}

}