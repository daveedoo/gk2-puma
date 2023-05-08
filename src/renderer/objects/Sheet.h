#pragma once
#include "Mesh.h"
class Sheet : public Mesh
{
private:
	virtual VertexData GetVertexData() const override;
};

