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

		static Ref<SceneHierarchyPanel> Create();

	private:
		Ref<Scene> m_Context;

	};

}