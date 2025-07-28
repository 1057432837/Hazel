#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		Timestep();

		~Timestep();

		Timestep(float time = 0.0f);

		float GetSeconds() const { return m_Time; }

		float GetMilliseconds() const { return m_Time * 1000.0f; }

		operator float() const { return m_Time; }

	private:
		float m_Time;

	};

}