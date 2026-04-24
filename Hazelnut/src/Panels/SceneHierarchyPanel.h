#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Scene/Scene.h"
#include "Hazel/Scene/Entity.h"

namespace Hazel {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel();

		~SceneHierarchyPanel();

		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		void DrawEntityNode(Entity entity);

		void DrawComponents(Entity entity);

		Entity GetSelectedEntity() const{ return m_SelectionContext; }

		void SetSelectedEntity(Entity entity) { m_SelectionContext = entity; }

		static Ref<SceneHierarchyPanel> Create();

	private:
		Ref<Scene> m_Context;

		Entity m_SelectionContext;

	};

}