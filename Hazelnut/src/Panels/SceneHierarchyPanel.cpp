#include "imgui/imgui.h"

#include "SceneHierarchyPanel.h"
#include "Hazel/Scene/Components.h"

namespace Hazel {
	SceneHierarchyPanel::SceneHierarchyPanel() {

	}

	SceneHierarchyPanel::~SceneHierarchyPanel() {

	}

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) {
		SetContext(context);

	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
		m_Context = context;
		
	}

	void SceneHierarchyPanel::OnImGuiRender() {
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.view<TagComponent>().each([&](auto entityID, auto& tc) {
			Entity entity{ entityID, m_Context.get() };
			ImGui::Text("%s", tc.Tag.c_str());

		});

		ImGui::End();

	}

	Ref<SceneHierarchyPanel> SceneHierarchyPanel::Create() {
		return CreateRef<SceneHierarchyPanel>();

	}

}