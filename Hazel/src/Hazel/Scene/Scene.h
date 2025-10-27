#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"
#include "Entity.h"

namespace Hazel {
	class Entity;

	class Scene
	{
		friend class Entity;

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

		static Ref<Scene> Create();

		Ref<Entity> CreateEntity(const std::string& name);

	private:
		entt::registry m_Registry;

	};

}