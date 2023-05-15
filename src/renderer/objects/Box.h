#pragma once
#include "Mesh.h"
class Box : public Mesh
{
public:
	Box();
private:
	virtual VerticesData GetVertexData() const override;
};

