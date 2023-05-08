#pragma once
#include "Mesh.h"
class Cylinder : public Mesh
{
private:
	virtual VertexData GetVertexData() const override;
};

