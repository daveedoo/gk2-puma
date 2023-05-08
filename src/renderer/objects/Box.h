#pragma once
#include "Mesh.h"
class Box : public Mesh
{
public:
	Box();
private:
	virtual VertexData GetVertexData() const override;
};

