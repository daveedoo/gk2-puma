#include "Arm.h"
#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../gl/ProgramFactory.h"=
#include "../VertexPosNormal.h"

Arm::Arm(std::string filename)
	: program(ProgramFactory::CreateProgram("shader.vert", "shader.frag"))
{
	glm::vec3 color(1.0f, 1.0f, 1.0f);

	this->program->SetVec3("color", color);

	// read data from filename line by line
	std::string filepath = "./res/" + filename;
	std::ifstream filestream(filepath);
	std::string line;
	std::vector<glm::vec3> vertexPositions;
	std::vector<VertexPosNormal> vertices;
	std::vector<std::array<unsigned int, 3>> triangles;
	std::getline(filestream, line);
	int vertexPositionCount = std::stoi(line);
	vertexPositions.reserve(vertexPositionCount);
	for (int i = 0; i < vertexPositionCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		float x, y, z;
		iss >> x >> y >> z;
		vertexPositions.push_back(glm::vec3(x, y, z));
	}
	std::getline(filestream, line);
	int vertexCount = std::stoi(line);
	vertices.reserve(vertexCount);
	for (int i = 0; i < vertexCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		int index;
		float x, y, z;
		iss >> index >> x >> y >> z;
		VertexPosNormal vertex = {
			vertexPositions[index],
			glm::vec3(x, y, z)
		};
		vertices.push_back(vertex);
	}
	std::getline(filestream, line);
	int triangleCount = std::stoi(line);
	triangles.reserve(triangleCount);
	this->triangleCount = triangleCount;
	for (int i = 0; i < triangleCount; i++)
	{
		std::getline(filestream, line);
		std::istringstream iss(line);
		unsigned int i1, i2, i3;
		iss >> i1 >> i2 >> i3;
		triangles.push_back({ i1, i2, i3 });
	}
	//TODO load edges
	filestream.close();

	this->vao = std::make_unique<GL::VAO>();
	this->vbo = std::make_unique<GL::VBO>(vertices.data(),
		sizeof(VertexPosNormal) * vertexCount);
	this->ebo = std::make_unique<GL::EBO>();
	this->ebo->SetBufferData(triangles.data(),
		GL::EBO::DataType::UINT, 3 * triangleCount);
	this->vao->DefineFloatAttribute(*this->vbo, 0, 3, 
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormal), 0);
	this->vao->DefineFloatAttribute(*this->vbo, 1, 3, 
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormal), sizeof(glm::vec3));
}

void Arm::Render(const Camera& camera) const
{
	this->vao->Bind();
	this->program->Use();
	this->program->SetMat4("worldMatrix", this->model);
	this->program->SetMat4("viewMatrix", camera.GetViewMatrix());
	this->program->SetMat4("projMatrix", camera.GetProjectionMatrix());

	glDrawElements(GL_TRIANGLES, this->triangleCount * 3, 
		static_cast<GLenum>(this->ebo->GetDataType()), static_cast<const void*>(0));
}
