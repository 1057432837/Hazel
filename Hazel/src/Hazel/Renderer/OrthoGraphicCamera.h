#pragma once

#include "glm/glm.hpp"

namespace Hazel {
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		~OrthographicCamera();

		const glm::vec3& GetPosition() const { return m_Position; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }

		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		void SetProjection(float left, float right, float bottom, float top);

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};

		float m_Rotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;

		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ViewProjectionMatrix;

		void RecalculateViewMatrix();

	};

}