#include "Box.h"

VertexData Box::GetVertexData() const
{
    unsigned int vertexCount = 24;
    unsigned int triangleCount = 12;

    std::vector<VertexPosNormal> vertices = {
        // bottom face
        { glm::vec3(-10.f, -1.f, -10.f), glm::vec3(0.f, 1.f, 0.f) },
        { glm::vec3(10.f, -1.f, -10.f), glm::vec3(0.f, 1.f, 0.f) },
        { glm::vec3(10.f, -1.f, 10.f), glm::vec3(0.f, 1.f, 0.f) },
        { glm::vec3(-10.f, -1.f, 10.f), glm::vec3(0.f, 1.f, 0.f) },
        // top face
		{ glm::vec3(-10.f, 9.f, -10.f), glm::vec3(0.f, -1.f, 0.f) },
		{ glm::vec3(10.f, 9.f, -10.f), glm::vec3(0.f, -1.f, 0.f) },
		{ glm::vec3(10.f, 9.f, 10.f), glm::vec3(0.f, -1.f, 0.f) },
		{ glm::vec3(-10.f, 9.f, 10.f), glm::vec3(0.f, -1.f, 0.f) },
        // front face
        { glm::vec3(-10.f, -1.f, -10.f), glm::vec3(0.f, 0.f, 1.f) },
        { glm::vec3(10.f, -1.f, -10.f), glm::vec3(0.f, 0.f, 1.f) },
		{ glm::vec3(10.f, 9.f, -10.f), glm::vec3(0.f, 0.f, 1.f) },
		{ glm::vec3(-10.f, 9.f, -10.f), glm::vec3(0.f, 0.f, 1.f) },
        // back face
		{ glm::vec3(-10.f, -1.f, 10.f), glm::vec3(0.f, 0.f, -1.f) },
		{ glm::vec3(10.f, -1.f, 10.f), glm::vec3(0.f, 0.f, -1.f) },
        { glm::vec3(10.f, 9.f, 10.f), glm::vec3(0.f, 0.f, -1.f) },
        { glm::vec3(-10.f, 9.f, 10.f), glm::vec3(0.f, 0.f, -1.f) },
        // left face
        { glm::vec3(-10.f, -1.f, -10.f), glm::vec3(1.f, 0.f, 0.f) },
		{ glm::vec3(-10.f, -1.f, 10.f), glm::vec3(1.f, 0.f, 0.f) },
		{ glm::vec3(-10.f, 9.f, 10.f), glm::vec3(1.f, 0.f, 0.f) },
		{ glm::vec3(-10.f, 9.f, -10.f), glm::vec3(1.f, 0.f, 0.f) },
        // right face
        { glm::vec3(10.f, -1.f, -10.f), glm::vec3(-1.f, 0.f, 0.f) },
        { glm::vec3(10.f, -1.f, 10.f), glm::vec3(-1.f, 0.f, 0.f) },
        { glm::vec3(10.f, 9.f, 10.f), glm::vec3(-1.f, 0.f, 0.f) },
		{ glm::vec3(10.f, 9.f, -10.f), glm::vec3(-1.f, 0.f, 0.f) },
    };

    std::vector<std::array<unsigned int, 3>> triangles = {
        { 0, 1, 2 },
        { 0, 2, 3 },
        { 4, 5, 6 },
		{ 4, 6, 7 },
		{ 8, 9, 10 },
		{ 8, 10, 11 },
		{ 12, 13, 14 },
		{ 12, 14, 15 },
		{ 16, 17, 18 },
		{ 16, 18, 19 },
		{ 20, 21, 22 },
		{ 20, 22, 23 }
    };

    return VertexData{ vertexCount, triangleCount, vertices, triangles };
}
