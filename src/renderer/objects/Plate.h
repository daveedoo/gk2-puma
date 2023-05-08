#pragma once
#include "../../Camera.h"
#include <memory>
#include "../../gl/wrappers/VAO.h"
#include "../../gl/wrappers/VBO.h"
#include "../../gl/wrappers/EBO.h"
#include "../../gl/wrappers/Program.h"

class Plate
{
private:
	float xPosition;
	float angle;
	float sideSize = 5.f;

	glm::mat4 model;

	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::EBO> ebo;
	std::unique_ptr<GL::Program> program;

public:
	Plate(float xPosition, float angle);
	void Render(const Camera& camera);
};
