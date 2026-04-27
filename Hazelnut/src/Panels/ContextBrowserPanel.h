#pragma once

namespace Hazel {
	class ContextBrowserPanel
	{
	public:
		ContextBrowserPanel();

		~ContextBrowserPanel();

		void OnImGuiRender();

		static Ref<ContextBrowserPanel> Create();

	private:
		inline static const char* s_AssetsDirectory = "assets";

	};

}