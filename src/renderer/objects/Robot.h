#pragma once
#include "Arm.h"
#include <array>

class Robot
{
public:
	Robot();
	void Render(const Camera& camera) const;
private:
	std::array<std::unique_ptr<Arm>, 6> arms;
	std::array<double, 5> angles = {
		0, 0, 0, 0, 0
	};
};

