#pragma once

#include "filesystem"

#include "Hazel/Renderer/Texture.h"

namespace Hazel {
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		~ContentBrowserPanel();

		void OnImGuiRender();

		static Ref<ContentBrowserPanel> Create();

	private:
		std::filesystem::path m_BaseDirectory;

		std::filesystem::path m_CurrentDirectory;

		Ref<Texture2D> m_DirectoryIcon;

		Ref<Texture2D> m_FileIcon;

	};

}