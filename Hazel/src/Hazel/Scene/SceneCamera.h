#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel {
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType
		{
			Perspective = 0,

			Orthographic = 1

		};

		SceneCamera();

		virtual ~SceneCamera();

		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		float GetOrthographicSize() const { return m_OrthographicSize; }

		void SetOrthographicSize(float size) { m_OrthographicSize = size; ReCalculateProjection(); }

		ProjectionType GetProjectionType() const { return m_ProjectionType; }

	private:
		void ReCalculateProjection();

		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_OrthographicSize = 10.0f;

		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 1.0f;

	};

}