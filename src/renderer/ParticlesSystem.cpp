#include "ParticlesSystem.h"
#include <memory>
#include "../gl/wrappers/VAO.h"
#include "../gl/ProgramFactory.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

int ParticlesSystem::PARTICLES_COUNT_CAP = 256;
float ParticlesSystem::MAX_AGE = 5.f;
float ParticlesSystem::EMISSION_RATE = 50.f;
glm::vec3 ParticlesSystem::GRAVITY_ACCELERATION = glm::vec3(0.f, -0.000981f, 0.f);

ParticlesSystem::ParticlesSystem(glm::vec3 startParticlesVelocity)
	: startParticlesVelocity(startParticlesVelocity),
	random(std::random_device{}())
{
	this->program = ProgramFactory::CreateProgram("particles.vert", "particles.frag");
	this->program->SetVec3("color", glm::vec3(1.f, 1.f, 1.f));
	this->program->SetFloat("maxAge", MAX_AGE);

	this->vao = std::make_unique<GL::VAO>();
	this->vbo = std::make_unique<GL::VBO>(nullptr, 0);
	this->vao->DefineFloatAttribute(*this->vbo, 0, 3,
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormalAge), 0);
	this->vao->DefineFloatAttribute(*this->vbo, 1, 3,
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormalAge), sizeof(glm::vec3));
	this->vao->DefineFloatAttribute(*this->vbo, 2, 3,
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormalAge), 2 * sizeof(glm::vec3));
}

void ParticlesSystem::Update(float dt, glm::vec3 sourcePosition)
{
	cumulatedTime += dt;

	for (auto& particle : this->particles)
	{
		particle.Update(dt, GRAVITY_ACCELERATION);
	}
	auto erased = std::erase_if(this->particles, [](Particle& particle)
		{
			return particle.age > MAX_AGE;
		});

	int particlesToCreate = PARTICLES_COUNT_CAP - this->particles.size();
	if (particlesToCreate > 0)
	{
		particlesToCreate = std::min(particlesToCreate, (int)(cumulatedTime * EMISSION_RATE));
		cumulatedTime -= particlesToCreate / EMISSION_RATE;

		for (size_t i = 0; i < particlesToCreate; i++)
		{
			particles.push_back(RandomParticle(sourcePosition));
		}
	}

	auto vertices = std::vector<VertexPosNormalAge>();
	for (auto& particle : this->particles)
	{
		glm::vec3 dir = particle.position - particle.prevPosition;
		vertices.push_back(VertexPosNormalAge{ particle.prevPosition, glm::vec3(1.f, 0.f, 0.f), particle.age });	// TODO: change normal vectors
		vertices.push_back(VertexPosNormalAge{ particle.position + 200.f * dir, glm::vec3(1.f, 0.f, 0.f), particle.age });
	}


	this->vbo->SetBufferData(vertices.data(), vertices.size() * sizeof(VertexPosNormalAge));
}

void ParticlesSystem::Render(const Camera& camera)
{
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::vec3 cameraPos = glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	this->vao->Bind();
	this->program->Use();
	this->program->SetMat4("worldMatrix", glm::mat4(1.f));
	this->program->SetMat4("viewMatrix", viewMatrix);
	this->program->SetMat4("projMatrix", camera.GetProjectionMatrix());

	glLineWidth(3.f);
	glDrawArrays(GL_LINES, 0, 2 * this->particles.size());
	glLineWidth(1.f);

	ImGui::DragInt("cap", &PARTICLES_COUNT_CAP, 1.f, 1);
	ImGui::DragFloat("max age", &MAX_AGE, 0.2f, 0.1f);
	ImGui::DragFloat("emission rate", &EMISSION_RATE, 1.f, 1.f, 200.f);
	ImGui::DragFloat3("gravity", glm::value_ptr(GRAVITY_ACCELERATION), 0.00001f, 0.f, 0.f, "%.5f");
}

Particle ParticlesSystem::RandomParticle(glm::vec3 position)
{
	//static auto random = std::random_device{}();
	static std::uniform_real_distribution<float> angleDist(-glm::half_pi<float>(), glm::half_pi<float>());

	auto angle = angleDist(random);
	glm::vec3 velocity = glm::rotateZ(this->startParticlesVelocity, angle);

	return Particle(position, velocity);
}
