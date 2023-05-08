#pragma once
#include "Mesh.h"
class Cylinder : public Mesh
{
public:
	Cylinder();
private:
	virtual VertexData GetVertexData() const override;
};

