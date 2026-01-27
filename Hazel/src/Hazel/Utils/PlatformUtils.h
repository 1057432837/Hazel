#pragma once

#include "string.h"

namespace Hazel {
	class FileDialogs
	{
	public:
		FileDialogs();

		~FileDialogs();

		static std::string OpenFile(const char* filter);

		static std::string SaveFile(const char* filter);

	private:

	};

}