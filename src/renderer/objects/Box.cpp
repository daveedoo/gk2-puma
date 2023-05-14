#include "Box.h"

Box::Box() : Mesh()
{
    this->color = glm::vec3(1.f, 1.f, .5f);
    this->program->SetVec3("color", this->color);
}

VerticesData Box::GetVertexData() const
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
        { 2, 1, 0 },
        { 3, 2, 0 },
        { 4, 5, 6 },
		{ 4, 6, 7 },
		{ 8, 9, 10 },
		{ 8, 10, 11 },
        { 14, 13, 12 },
        { 15, 14, 12 },
        { 18, 17, 16 },
        { 19, 18, 16 },
		{ 20, 21, 22 },
		{ 20, 22, 23 }
    };

    return VerticesData{ vertexCount, triangleCount, vertices, triangles };
}
