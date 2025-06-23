#include "hzpch.h"

#include "Timestep.h"

namespace Hazel {

	Timestep::Timestep(float time = 0.0f) : m_Time(time) {

	}

	Timestep::~Timestep() {

	}

	float Timestep::GetSeconds() const {
		return m_Time;
	
	}

	float Timestep::GetMilliseconds() const {
		return m_Time * 1000.0f;
	
	}

	Timestep::operator float() const {
		return m_Time;
	
	}

}