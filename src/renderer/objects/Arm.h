#pragma once
#include <memory>
#include "../../gl/wrappers/VAO.h"
#include "../../gl/wrappers/Program.h"
#include "../../Camera.h"
#include "../../gl/wrappers/EBO.h"

struct VertexPosNormal
{
	glm::vec3 position;
	glm::vec3 normal;
};

class Arm
{
public:
	Arm(std::string filename);
	void Render(const Camera& camera) const;
	void SetModel(const glm::mat4& model) {
		this->model = model;
	}
private:
	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::EBO> ebo;
	std::unique_ptr<GL::Program> program;
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int triangleCount;
};

