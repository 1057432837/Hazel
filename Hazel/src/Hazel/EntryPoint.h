#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

//入口函数
int main(int argc, char** argv) {
	//初始化日志
	Hazel::Log::Init();
	HZ_CORE_WARN("Hazel Log Initialized!");
	HZ_CLIENT_INFO("Sandbox Log Initialized!");

	//调用SandboxApp的CreateApplication()函数
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;

}

#endif