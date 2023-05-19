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

struct VerticesData
{
	unsigned int vertexCount;
	unsigned int triangleCount;
	std::vector<VertexPosNormal> vertices;
	std::vector<std::array<unsigned int, 3>> triangles;
	// Two vertices on the edge, and two vertices on either side
	std::vector<std::array<unsigned int, 4>> edges;
};

class Mesh
{
public:
	Mesh();
	virtual void Render(const Camera& camera);
	virtual void DrawShadowVolumes(const Camera& camera);
	void SetModel(const glm::mat4& model) {
		this->model = model;
	}
	void SetLight(bool enable);
	void Initialize();
protected:
	virtual VerticesData GetVerticesData() const = 0;
	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::EBO> ebo;
	std::unique_ptr<GL::VAO> shadowVAO;
	std::unique_ptr<GL::EBO> shadowEBO;
	std::unique_ptr<GL::Program> program;
	std::unique_ptr<GL::Program> shadowVolumeProgram;
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int triangleCount;
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
private:
	bool initialized = false;
};

