#pragma once
#include <memory>
#include <array>
#include "../../gl/wrappers/VAO.h"
#include "../../gl/wrappers/Program.h"
#include "../../Camera.h"
#include "../../gl/wrappers/EBO.h"

struct VertexPosNormal
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct VertexData
{
	unsigned int vertexCount;
	unsigned int triangleCount;
	std::vector<VertexPosNormal> vertices;
	std::vector<std::array<unsigned int, 3>> triangles;
	//TODO edges
};

class Mesh
{
public:
	Mesh();
	virtual void Render(const Camera& camera);
	void SetModel(const glm::mat4& model) {
		this->model = model;
	}
	void Initialize();
protected:
	virtual VertexData GetVertexData() const = 0;
	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::EBO> ebo;
	std::unique_ptr<GL::Program> program;
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int triangleCount;
private:
	bool initialized = false;
};

