#pragma once

#include "glm/glm.hpp"

namespace Hazel {
	class OrthoGraphicCamera
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);

		~OrthoGraphicCamera();

		const glm::vec3& GetPosition() const;

		void SetPosition(const glm::vec3& position);

		float GetRotation() const;

		void SetRotation(float rotation);

		const glm::mat4& GetProjectionMatrix() const;

		const glm::mat4& GetViewMatrix() const;

		const glm::mat4& GetViewProjectionMatrix() const;

	private:
		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};

		float m_Rotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;

		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ViewProjectionMatrix;

		void RecalculateViewMatrix();

	};

}