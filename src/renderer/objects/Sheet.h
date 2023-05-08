#pragma once
#include "Mesh.h"
class Sheet : public Mesh
{
public:
	Sheet();
private:
	virtual VertexData GetVertexData() const override;
};

