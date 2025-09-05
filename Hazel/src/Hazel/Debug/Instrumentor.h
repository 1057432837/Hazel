#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Hazel {
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;

	};

	struct InstrumentationSession
	{
		std::string Name;

	};

	class Instrumentor
	{
	public:
		Instrumentor();

		~Instrumentor();

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");

		void EndSession();

		void WriteProfile(const ProfileResult& result);

		void WriteHeader();

		void WriteFooter();

		static Instrumentor& Get();

	private:
		InstrumentationSession* m_CurrentSession;

		std::ofstream m_OutputStream;

		int m_ProfileCount;

	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer();

		~InstrumentationTimer();

		InstrumentationTimer(const char* name);

		void Stop();

	private:
		const char* m_Name;

		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

		bool m_Stopped;

	};

}

#define HZ_PROFILE 1
#if HZ_PROFILE
#define HZ_PROFILE_BEGIN_SESSION(name, filepath) ::Hazel::Instrumentor::Get().BeginSession(name, filepath)
#define HZ_PROFILE_END_SESSION() ::Hazel::Instrumentor::Get().EndSession()
#define HZ_PROFILE_SCOPE(name) ::Hazel::InstrumentationTimer timer##__LINE__(name);
#define HZ_PROFILE_FUNCTION() HZ_PROFILE_SCOPE(__FUNCSIG__)
#else
#define HZ_PROFILE_BEGIN_SESSION(name, filepath) 
#define HZ_PROFILE_END_SESSION() 
#define HZ_PROFILE_SCOPE(name) 
#define HZ_PROFILE_FUNCTION()
#endif