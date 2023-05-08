#pragma once
#include "Mesh.h"
class Box : public Mesh
{
private:
	virtual VertexData GetVertexData() const override;
};

