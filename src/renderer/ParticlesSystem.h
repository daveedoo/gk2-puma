#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../renderer/objects/Mesh.h"
#include <random>


struct VertexPosNormalAge
{
	glm::vec3 position;
	glm::vec3 normal;
	float age;
};

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
		velocity += acceleration * dt;
		prevPosition = position;
		position += velocity;
		age += dt;
	}
};

class ParticlesSystem
{
private:
	static int PARTICLES_COUNT_CAP;
	static float MAX_AGE;					// in seconds
	static float EMISSION_RATE;			// number of particles emitted per second
	static glm::vec3 GRAVITY_ACCELERATION;

	std::vector<Particle> particles;
	glm::vec3 startParticlesVelocity;

	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::Program> program;

	std::default_random_engine random;
	float cumulatedTime = 0.f;

public:
	ParticlesSystem(glm::vec3 startParticlesVelocity);

	void Update(float dt, glm::vec3 sourcePosition);
	void Render(const Camera& camera);

private:
	Particle RandomParticle(glm::vec3 position);
};
