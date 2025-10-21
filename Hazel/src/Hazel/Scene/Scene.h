#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"

namespace Hazel {
	class Scene
	{
	public:
#if ENTT_EXAMPLE_CODE
		struct MeshComponent {
			bool Data;
			MeshComponent() = default;

		};

		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;

			TransformComponent(const TransformComponent&) = default;

			TransformComponent(const glm::mat4& transform) : Transform(transform) {}

			operator glm::mat4& () { return Transform; }

			operator const glm::mat4& () const { return Transform; }

		}transform;

#endif

		Scene();

		~Scene();

		void OnUpdate(Timestep ts);

		entt::entity CreateEntity();

		entt::registry& Reg() { return m_Registry; }

	private:
		entt::registry m_Registry;

	};

}