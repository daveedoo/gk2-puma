#pragma once
#include "Mesh.h"

class Arm : public Mesh
{
public:
	Arm(std::string filename) : Mesh(), filename(filename) {}
private:
	std::string filename;
	virtual VerticesData GetVertexData() const override;
};

