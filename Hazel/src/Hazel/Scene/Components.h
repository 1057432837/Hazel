#pragma once

#include "glm/glm.hpp"

#include "Hazel/Renderer/OrthoGraphicCamera.h"
#include "Hazel/Renderer/Camera.h"

namespace Hazel {
	class TagComponent
	{
	public:
		std::string Tag;

		TagComponent() = default;

		TagComponent(const TagComponent&) = default;

		TagComponent(const std::string& tag) : Tag(tag) { }

	private:

	};

	class TransformComponent {
	public:
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(const glm::mat4& transform) : Transform(transform) { }

		operator glm::mat4& () { return Transform; }

		operator const glm::mat4& () const { return Transform; }

	private:

	};

	class SpriteRendererComponent {
	public:
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		
		SpriteRendererComponent(const glm::vec4& color) : Color(color) { }

	private:

	};

	class CameraComponent {
	public:
		Camera Camera;

		bool Primary = true;

		bool FixedAspectRatio = false;

		CameraComponent() = default;
		
		CameraComponent(const CameraComponent&) = default;
		
		CameraComponent(const glm::mat4& projection) : Camera(projection) { }

	private:

	};

}