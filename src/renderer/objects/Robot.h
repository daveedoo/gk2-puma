#pragma once
#include "Arm.h"
#include <array>
#include "../../Window/input/events/modded/KeyEvent.h"

class Robot
{
public:
	Robot();
	void Render(const Camera& camera) const;
	bool HandleKey(const KeyEvent& keyEvent);
	void SetArmPosition(const glm::vec3& pos, const glm::vec3& normal);
private:
	std::array<std::unique_ptr<Arm>, 6> arms;
	std::array<float, 5> angles = {
		0.f, 0.f, 0.f, 0.f, 0.f
	};
	const static double angleStep;

	void updateArms();
};

