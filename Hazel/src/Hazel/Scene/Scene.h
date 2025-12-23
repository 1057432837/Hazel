#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"
#include "Entity.h"

namespace Hazel {
	class Entity;

	class Scene
	{
	public:
#if ENTT_EXAMPLE_CODE
		class MeshComponent {
		public:
			bool Data;
			MeshComponent() = default;

		private:

		};

		class TransformComponent
		{
		public:
			glm::mat4 Transform;

			TransformComponent() = default;

			TransformComponent(const TransformComponent&) = default;

			TransformComponent(const glm::mat4& transform) : Transform(transform) {}

			operator glm::mat4& () { return Transform; }

			operator const glm::mat4& () const { return Transform; }

		private:

		}transform;

#endif

		Scene();

		~Scene();

		void OnUpdate(Timestep ts);

		void OnViewportResize(uint32_t width, uint32_t height);

		static Ref<Scene> Create();

		Ref<Entity> CreateEntity(const std::string& name);

	private:
		entt::registry m_Registry;

		uint32_t m_ViewportWidth = 0;

		uint32_t m_ViewportHeight = 0;

		friend class Entity;

		friend class SceneHierarchyPanel;

	};

}