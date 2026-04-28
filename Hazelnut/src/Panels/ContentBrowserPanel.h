#pragma once

#include "filesystem"

namespace Hazel {
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		~ContentBrowserPanel();

		void OnImGuiRender();

		static Ref<ContentBrowserPanel> Create();

	private:
		std::filesystem::path m_CurrentDirectory;

	};

}