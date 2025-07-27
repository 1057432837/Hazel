#include "hzpch.h"

#include "Timestep.h"

namespace Hazel {
	Timestep::Timestep() {

	}

	Timestep::~Timestep() {

	}

	Timestep::Timestep(float time) : m_Time(time) {

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