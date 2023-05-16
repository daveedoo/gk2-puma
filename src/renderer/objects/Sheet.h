#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class Sheet : public Mesh
{
private:
	glm::vec3 position;
	float angle;

	virtual VerticesData GetVertexData() const override;

public:
	Sheet(glm::vec3 position, float angle);
	glm::vec3 GetCenterPosition() { return this->position; }
	float GetSlopeAngle() { return this->angle; }
};

