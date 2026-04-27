#include "hzpch.h"
#include "filesystem"

#include "imgui/imgui.h"

#include "ContextBrowserPanel.h"

namespace Hazel {
	ContextBrowserPanel::ContextBrowserPanel() {

	}

	ContextBrowserPanel::~ContextBrowserPanel() {

	}

	void ContextBrowserPanel::OnImGuiRender() {
		ImGui::Begin("Context Browser");

		for (auto& p : std::filesystem::directory_iterator(s_AssetsDirectory))
		{
			std::string path = p.path().string();
			ImGui::Text("%s", path.c_str());
			ImGui::Separator();

		}

		ImGui::End();

	}

	Ref<ContextBrowserPanel> ContextBrowserPanel::Create() {
		return CreateRef<ContextBrowserPanel>();

	}

}