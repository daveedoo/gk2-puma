#include "ParticlesSystem.h"


const int ParticlesSystem::PARTICLES_COUNT_CAP = 32;
const float ParticlesSystem::MAX_AGE = 3.f;
const float ParticlesSystem::EMISSION_RATE = 5.f;
const glm::vec3 ParticlesSystem::GRAVITY_ACCELERATION = glm::vec3(0.f, -9.81f, 0.f);

void ParticlesSystem::Update(float dt, glm::vec3 sourcePosition)
{
	for (auto& particle : this->particles)
	{
		particle.Update(dt, GRAVITY_ACCELERATION);
	}
	std::erase_if(this->particles, [](Particle& particle)
		{
			return particle.age > MAX_AGE;
		});

	int particlesToCreate = PARTICLES_COUNT_CAP - this->particles.size();
	if (particlesToCreate > 0)
	{
		particlesToCreate = std::min(particlesToCreate, (int)(dt * EMISSION_RATE));
		for (size_t i = 0; i < particlesToCreate; i++)
		{
			particles.push_back(RandomParticle(sourcePosition));
		}
	}
}

Particle ParticlesSystem::RandomParticle(glm::vec3 position)
{
	return Particle(position, this->startParticlesVelocity);
}
