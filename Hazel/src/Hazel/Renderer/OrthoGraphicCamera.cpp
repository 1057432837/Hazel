#include "hzpch.h"

#include "glm/gtc/matrix_transform.hpp"

#include "OrthoGraphicCamera.h"

namespace Hazel {
	OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float bottom, float top) : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	OrthoGraphicCamera::~OrthoGraphicCamera() {

	}

	const glm::vec3& OrthoGraphicCamera::GetPosition() const {
		return m_Position;

	}

	void OrthoGraphicCamera::SetPosition(const glm::vec3& position) {
		m_Position = position; RecalculateViewMatrix();

	}

	float OrthoGraphicCamera::GetRotation() const {
		return m_Rotation;
	
	}

	void OrthoGraphicCamera::SetRotation(float rotation) {
		m_Rotation = rotation; RecalculateViewMatrix();
	
	}

	const glm::mat4& OrthoGraphicCamera::GetProjectionMatrix() const {
		return m_ProjectionMatrix;
	
	}

	const glm::mat4& OrthoGraphicCamera::GetViewMatrix() const {
		return m_ViewMatrix;
	
	}

	const glm::mat4& OrthoGraphicCamera::GetViewProjectionMatrix() const {
		return m_ViewProjectionMatrix;
	
	}

	void OrthoGraphicCamera::RecalculateViewMatrix() {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

}