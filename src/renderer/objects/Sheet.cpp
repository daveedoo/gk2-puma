#include "Sheet.h"
#include <glm/gtx/rotate_vector.hpp>

Sheet::Sheet(glm::vec3 position, float angle) :
	position(position), angle(angle)
{
	this->color = glm::vec3(.5f, .5f, .5f);
	this->program->SetVec3("color", this->color);

	auto modelMtx = glm::mat4(1.f);
	modelMtx = glm::translate(modelMtx, this->position);
	modelMtx = glm::rotate(modelMtx, this->angle, glm::vec3(0.f, 0.f, 1.f));
	SetModel(modelMtx);
}

VerticesData Sheet::GetVerticesData() const
{
	unsigned int vertexCount = 8;
	unsigned int triangleCount = 4;

	std::vector<VertexPosNormal> vertices(vertexCount);
	glm::vec3 normal = glm::vec3(1.f, 0.f, 0.f);

	glm::vec3 pos = glm::vec3(0.f, -1.f, -1.f);
	vertices[0] = { pos, normal };
	vertices[4] = { pos, -normal };
	pos = glm::vec3(0.f, -1.f, 1.f);
	vertices[1] = { pos, normal };
	vertices[5] = { pos, -normal };
	pos = glm::vec3(0.f, 1.f, 1.f);
	vertices[2] = { pos, normal };
	vertices[6] = { pos, -normal };
	pos = glm::vec3(0.f, 1.f, -1.f);
	vertices[3] = { pos, normal };
	vertices[7] = { pos, -normal };

	std::vector<std::array<unsigned int, 3>> triangles = {
		{ 2, 1, 0 },
		{ 3, 2, 0 },
		{ 4, 5, 6 },
		{ 4, 6, 7 }
	};

	return { vertexCount, triangleCount, vertices, triangles };
}
