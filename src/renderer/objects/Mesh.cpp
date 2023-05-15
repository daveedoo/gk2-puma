#include "Mesh.h"
#include "../../gl/ProgramFactory.h"

Mesh::Mesh()
	: program(ProgramFactory::CreateProgram("shader.vert", "shader.frag"))
{
	this->program->SetVec3("color", this->color);
	glm::vec3 lightPos(-1.0f, 4.0f, 1.0f);
	this->program->SetVec3("lightPos", lightPos);
}

void Mesh::Render(const Camera& camera)
{
	if (!this->initialized) Initialize();

	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::vec3 cameraPos = glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	this->vao->Bind();
	this->program->Use();
	this->program->SetMat4("worldMatrix", this->model);
	this->program->SetMat4("viewMatrix", viewMatrix);
	this->program->SetMat4("projMatrix", camera.GetProjectionMatrix());
	this->program->SetVec3("cameraPos", cameraPos);

	glDrawElements(GL_TRIANGLES, this->triangleCount * 3,
		static_cast<GLenum>(this->ebo->GetDataType()), static_cast<const void*>(0));
}

void Mesh::Initialize()
{
	VerticesData data = this->GetVertexData();
	this->triangleCount = data.triangleCount;

	this->vao = std::make_unique<GL::VAO>();
	this->vbo = std::make_unique<GL::VBO>(data.vertices.data(),
		sizeof(VertexPosNormal) * data.vertexCount);
	this->ebo = std::make_unique<GL::EBO>();
	this->ebo->SetBufferData(data.triangles.data(),
		GL::EBO::DataType::UINT, 3 * data.triangleCount);
	this->vao->DefineFloatAttribute(*this->vbo, 0, 3,
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormal), 0);
	this->vao->DefineFloatAttribute(*this->vbo, 1, 3,
		GL::VAO::FloatAttribute::FLOAT, sizeof(VertexPosNormal), sizeof(glm::vec3));

	this->initialized = true;
}
