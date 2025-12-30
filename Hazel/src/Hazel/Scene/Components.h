#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Hazel/Renderer/OrthoGraphicCamera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"

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
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };

		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };

		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(const glm::vec3& translation) : Translation(translation) { }

		glm::mat4 GetTransform() const { glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 }) * glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) * glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 }); return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale); }

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
		SceneCamera Camera;

		bool Primary = true;

		bool FixedAspectRatio = false;

		CameraComponent() = default;
		
		CameraComponent(const CameraComponent&) = default;

	private:

	};

	class NativeScriptComponent
	{
	public:
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind() {
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };

		}

	private:

	};

}