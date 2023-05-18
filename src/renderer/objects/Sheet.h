#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>

class Sheet : public Mesh
{
private:
	glm::vec3 position;
	float angle;

	virtual VerticesData GetVerticesData() const override;

public:
	Sheet(glm::vec3 position, float angle);
	const glm::vec3& GetCenterPosition() const { return this->position; }
	float GetSlopeAngle() const { return this->angle; }
};

