#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		Timestep(float time);

		~Timestep();

		float GetSeconds() const;

		float GetMilliseconds() const;

		operator float() const;

	private:
		float m_Time;

	};

}