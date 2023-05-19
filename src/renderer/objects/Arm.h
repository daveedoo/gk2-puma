#pragma once
#include "Mesh.h"

class Arm : public Mesh
{
public:
	Arm(std::string filename) : Mesh(), filename(filename) {}
private:
	std::string filename;
	virtual VerticesData GetVerticesData() const override;
	unsigned int GetRemainingIndex(VerticesData& data, std::vector<glm::vec3> vertexPositions, unsigned int triangleIndex,
		unsigned int v1, unsigned int v2) const;
};

