#pragma once
#include <glm/glm.hpp>
#include <vector>


struct Particle
{
	glm::vec3 prevPosition;
	glm::vec3 position;
	glm::vec3 velocity;
	float age;

	Particle(const glm::vec3& position, const glm::vec3& velocity)
		: prevPosition(position), position(position), velocity(velocity), age(0.0)
	{
	}

	void Update(float dt, glm::vec3 acceleration)
	{
		velocity += acceleration;
		prevPosition = position;
		position += velocity;
		age += dt;
	}
};

class ParticlesSystem
{
private:
	static const int PARTICLES_COUNT_CAP;
	static const float MAX_AGE;					// in seconds
	static const float EMISSION_RATE;			// number of particles emitted per second
	static const glm::vec3 GRAVITY_ACCELERATION;

	std::vector<Particle> particles;
	glm::vec3 startParticlesVelocity;

public:
	ParticlesSystem(glm::vec3 startParticlesVelocity)
		: startParticlesVelocity(startParticlesVelocity) {}

	void Update(float dt, glm::vec3 sourcePosition);

private:
	Particle RandomParticle(glm::vec3 position);
};
