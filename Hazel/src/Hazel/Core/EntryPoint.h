#pragma once
#include "filesystem"

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

//Èë¿Úº¯Êý
int main(int argc, char** argv) {
	std::filesystem::create_directories("../cache");

	Hazel::Log::Init();

	HZ_PROFILE_BEGIN_SESSION("Startup", "../cache/HazelProfile-Startup.json");
	auto app = Hazel::CreateApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "../cache/HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Shutdown", "../cache/HazelProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();

}

#endif