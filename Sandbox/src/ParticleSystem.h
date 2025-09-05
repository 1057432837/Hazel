#pragma once

#include "Hazel.h"

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity;
	glm::vec2 VelocityVariation;
	glm::vec4 ColorBegin;
	glm::vec4 ColorEnd;
	float SizeBegin;
	float SizeEnd;
	float SizeVariation;
	float LifeTime = 1.0f;

};

class ParticleSystem
{
public:
	//ParticleSystem();

	~ParticleSystem();

	ParticleSystem(uint32_t maxParticles = 100);

	void OnUpdate(Hazel::Timestep ts);

	void OnRender(Hazel::OrthographicCamera& camera);

	void Emit(const ParticleProps& particleProps);

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;

	};

	std::vector<Particle> m_ParticlePool;

	uint32_t m_PoolIndex;

	Hazel::Ref<Hazel::Renderer2D> m_Renderer2D;

};