#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		Timestep();

		~Timestep();

		Timestep(float time = 0.0f);

		float GetSeconds() const;

		float GetMilliseconds() const;

		operator float() const;

	private:
		float m_Time;

	};

}