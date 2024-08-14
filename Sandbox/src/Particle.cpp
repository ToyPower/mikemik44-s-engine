#include <hzpch.h>
#include "Particle.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem(uint32_t size) : m_PoolIndex(size-1)
{
	m_ParticlePool.resize(size);
}

void ParticleSystem::OnUpdate(ME::TimeStep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;
	
		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}
void ParticleSystem::OnRender(ME::Ref<ME::Camera>& camera)
{
	
	ME::Renderer2D::beginScene(camera);
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		//color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

		
		ME::Renderer2D::setRotation(particle.Rotation);
		ME::Renderer2D::drawQuadCentered({ particle.Position.x,particle.Position.y,0.2f}, { size,size }, color);
		ME::Renderer2D::setRotation(0);
		
	}
	ME::Renderer2D::endScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = ME::Rand::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (ME::Rand::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (ME::Rand::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (ME::Rand::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}