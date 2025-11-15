#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel {
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();

		virtual ~SceneCamera();

		void SetOrthographic(float size, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

	private:
		void ReCalculateProjection();

		float m_OrthographicSize = 10.0f;

		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 1.0f;

	};

}