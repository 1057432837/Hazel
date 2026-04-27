#pragma once

#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Hazel/Renderer/EditorCamera.h"
#include "Panels/ContextBrowserPanel.h"

namespace Hazel {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual ~EditorLayer();

		virtual void OnAttach() override;

		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;

		virtual void OnImGuiRender() override;

		void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();

		void OpenScene();

		void SaveSceneAs();

		Ref<VertexArray> m_SquareVA;

		Ref<OrthographicCameraController> m_CameraController;

		Ref<Shader> m_FlatColorShader;

		Ref<Renderer> m_Renderer;

		Ref<Renderer2D> m_Renderer2D;

		Ref<Texture2D> m_CheckerboardTexture;

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		bool m_ViewportFocused = false;

		bool m_ViewportHovered = false;

		Ref<FramebufferSpecification> m_FbSpec;

		Ref<Entity> m_SquareEntity;

		Ref<Entity> m_CameraEntity;

		Ref<Entity> m_SecondCamera;

		Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;

		bool m_PrimaryCamera = true;

		Ref<EditorCamera> m_EditorCamera;

		int m_GizmoType = -1;

		glm::vec2 m_ViewportBounds[2];

		Entity m_HoveredEntity;

		Ref<ContextBrowserPanel> m_ContextBrowserPanel;

	};

}