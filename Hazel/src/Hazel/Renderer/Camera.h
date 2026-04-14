#pragma once

#include "glm/glm.hpp"

#include "Hazel/Core/Core.h"

namespace Hazel {
	class Camera
	{
	public:
		Camera() = default;

		virtual ~Camera() = default;

		Camera(const glm::mat4& projection)	: m_Projection(projection) { }

		const glm::mat4& GetProjection() const { return m_Projection; }

		static Ref<Camera> Create(float fov, float aspectRatio, float nearClip, float farClip);

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);

	};

}