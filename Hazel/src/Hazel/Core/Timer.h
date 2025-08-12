#pragma once

#include "chrono"

namespace Hazel {
	template<typename Fn>
	class Timer
	{
	public:
		Timer() {

		}

		~Timer() {
			if (!m_Stopped)
			{
				Stop();

			}

		}

		Timer(const char* name, Fn&& func) : m_Name(name), m_Func(func), m_Stopped(false) {
			m_StartTimePoint = std::chrono::steady_clock::now();

		}

		void Stop() {
			auto endTimePoint = std::chrono::steady_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

			m_Stopped = true;

			auto duration = (end - start) * 0.001f;
			m_Func({ m_Name, duration });

		}

	private:
		const char* m_Name;

		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;

		bool m_Stopped;

		Fn m_Func;

	};

}