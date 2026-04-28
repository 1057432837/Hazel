#include "hzpch.h"
#include "filesystem"

#include "imgui/imgui.h"

#include "ContentBrowserPanel.h"

namespace Hazel {
	static const std::filesystem::path s_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetPath) {

	}

	ContentBrowserPanel::~ContentBrowserPanel() {

	}

	void ContentBrowserPanel::OnImGuiRender() {
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();

			}

		}

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();
			if (directoryEntry.is_directory())
			{
				if (ImGui::Button(filenameString.c_str()))
				{
					m_CurrentDirectory /= path.filename();

				}

			}
			else {
				if (ImGui::Button(filenameString.c_str()))
				{

				}

			}

		}

		ImGui::End();

	}

	Ref<ContentBrowserPanel> ContentBrowserPanel::Create() {
		return CreateRef<ContentBrowserPanel>();

	}

}