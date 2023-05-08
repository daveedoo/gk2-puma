#include "Plate.h"
#include <array>
#include <glm/gtx/transform.hpp>
#include "../../gl/ProgramFactory.h"
#include "../VertexPosNormal.h"

Plate::Plate(float xPosition, float angle)
	: xPosition(xPosition),
	angle(glm::degrees(angle)),
	program(ProgramFactory::CreateProgram("shader.vert", "shader.frag"))
{
	this->program->SetVec3("color", glm::vec3(0.7f));

	float halfSide = sideSize / 2.f;
	auto arr = std::array<VertexPosNormal, 4>
	{
		VertexPosNormal{ glm::vec3(0.f, -halfSide, halfSide), glm::vec3(1.f, 0.f, 0.f) },
		VertexPosNormal{ glm::vec3(0.f, -halfSide, -halfSide), glm::vec3(1.f, 0.f, 0.f) },
		VertexPosNormal{ glm::vec3(0.f, halfSide, -halfSide), glm::vec3(1.f, 0.f, 0.f) },
		VertexPosNormal{ glm::vec3(0.f, halfSide, halfSide), glm::vec3(1.f, 0.f, 0.f) }
	};

	this->model = glm::rotate(this->angle, glm::vec3(0.f, 0.f, 1.f));
	this->model = glm::translate(this->model, glm::vec3(xPosition, 0.f, 0.f));
	for (size_t i = 0; i < 4; i++)
	{
		arr[i].position = glm::vec3(this->model * glm::vec4(arr[i].position, 1.f));
		arr[i].normal = glm::vec3(this->model * glm::vec4(arr[i].normal, 0.f));
	}
	auto indexes = std::array<unsigned short, 6>
	{
		0, 1, 3,
		1, 2, 3
	};

	this->vao = std::make_unique<GL::VAO>();
	this->ebo = std::make_unique<GL::EBO>();
	this->ebo->SetBufferData(indexes.data(), GL::EBO::DataType::USHORT, 6);
	this->vbo = std::make_unique<GL::VBO>(arr.data(), sizeof(arr));
	this->vao->DefineFloatAttribute(*this->vbo, 0, 3, GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormal), 0);
}

void Plate::Render(const Camera& camera)
{
	this->vao->Bind();
	this->program->Use();
	this->program->SetMat4("worldMatrix", glm::identity<glm::mat4>());
	this->program->SetMat4("viewMatrix", camera.GetViewMatrix());
	this->program->SetMat4("projMatrix", camera.GetProjectionMatrix());

	glDrawElements(GL_TRIANGLES, 6, static_cast<GLenum>(this->ebo->GetDataType()), static_cast<const void*>(0));
}
