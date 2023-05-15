#include "Cylinder.h"
#include <glm/gtc/constants.hpp>

Cylinder::Cylinder()
{
    this->color = glm::vec3(0.f, .5f, 0.f);
    this->program->SetVec3("color", this->color);
}

VerticesData Cylinder::GetVertexData() const
{
    glm::vec3 center = glm::vec3(.5f, -1.f, -2.f);
    float radius = .5f;
    float height = 4.f;
    unsigned int slices = 20;
    unsigned int vertexCount = 4 * slices + 2;
    unsigned int triangleCount = 4 * slices;
    std::vector<VertexPosNormal> vertices(vertexCount);
    std::vector<std::array<unsigned int, 3>> triangles(triangleCount);

    float xDiff = height / 2.f;
    glm::vec3 normal = glm::vec3(1.f, 0.f, 0.f);
    for (int i = 0; i < slices; i++) {
        float alpha = 2 * glm::pi<float>() * i / slices;
        float yDiff = radius * glm::cos(alpha);
        float zDiff = radius * glm::sin(alpha);
        glm::vec3 pos1 = center + glm::vec3(xDiff, yDiff, zDiff);
        vertices[i] = { pos1, normal };
        glm::vec3 pos2 = center + glm::vec3(-xDiff, yDiff, zDiff);
        vertices[slices + i] = { pos2, -normal };

        glm::vec3 norm = glm::vec3(0.f, glm::cos(alpha), glm::sin(alpha));
        vertices[2 * slices + i] = { pos1, norm };
        vertices[3 * slices + i] = { pos2, norm };
    }
    vertices.end()[-2] = { center + glm::vec3(xDiff, 0.f, 0.f), normal };
    vertices.end()[-1] = { center + glm::vec3(-xDiff, 0.f, 0.f), -normal };

    for (unsigned int i = 0; i < slices; i++) {
        unsigned int iNext = (i + 1) % slices;
		triangles[i] = { i, iNext, vertexCount - 2 };
		triangles[slices + i] = { slices + i, vertexCount - 1, slices + iNext };
        triangles[2 * slices + i] = { 2 * slices + i, 3 * slices + i, 2 * slices + iNext };
        triangles[3 * slices + i] = { 3 * slices + i, 3 * slices + iNext, 2 * slices + iNext };
	}

    return { vertexCount, triangleCount, vertices, triangles };
}
