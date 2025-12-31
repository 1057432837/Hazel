#pragma once

#include "entt.hpp"

#include "Scene.h"

namespace Hazel {
	class Scene;

	class Entity
	{
	public:
		Entity();

		~Entity();

		Entity(entt::entity handle, Scene* scene);

		Entity(const Entity& other);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			HZ_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);

		}

		template<typename T>
		T& GetComponent() {
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		
		}

		template<typename T>
		bool HasComponent() {
			if (!m_Scene) {
				return false;

			}

			if (!m_Scene->IsEntityValid(m_EntityHandle)) {
				return false;
			
			}

			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		
		}

		template<typename T>
		void RemoveComponent() {
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		
		}

		operator bool() const { return (uint32_t)m_EntityHandle != 0; }

		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		operator entt::entity() const { return m_EntityHandle; }

		bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }

		bool operator!=(const Entity& other) const { return !(*this == other); }

	private:
		entt::entity m_EntityHandle{ entt::null };
		
		Scene* m_Scene = nullptr;

	};

}