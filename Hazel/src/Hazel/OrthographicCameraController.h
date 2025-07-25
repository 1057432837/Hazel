#pragma once

#include "Hazel/Renderer/OrthoGraphicCamera.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController();

		~OrthographicCameraController();

		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);

		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }

		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		float GetZoomLevel(float level) { return m_ZoomLevel; }

		static OrthographicCameraController* Create(float aspectRatio, bool rotation);
		
	private:
		float m_AspectRatio;

		float m_ZoomLevel = 1.0f;

		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };

		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f;

		float m_CameraRotationSpeed = 100.0f;

		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool OnWindowResized(WindowResizeEvent& e);

	};

}