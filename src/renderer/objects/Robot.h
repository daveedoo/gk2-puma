#pragma once
#include "Arm.h"
#include <array>
#include "../../Window/input/events/modded/KeyEvent.h"

class Robot
{
private:
	bool animation = false;
	double time = 0.0;
	glm::vec3 circleCenter = glm::vec3(0.f);
	float circleRadius = 1.f;
	float slopeAngle = 0.f;

public:
	Robot();
	void Render(const Camera& camera) const;
	void Update(double dt);
	bool HandleKey(const KeyEvent& keyEvent);
	
	void StartAnimation(glm::vec3 circleCenter, float circleRadius, float slopeAngle);
	void StopAnimation();

private:
	void updateArms();
	void SetArmPosition(const glm::vec3& pos, const glm::vec3& normal);
	std::array<std::unique_ptr<Arm>, 6> arms;
	std::array<float, 5> angles = {
		0.f, 0.f, 0.f, 0.f, 0.f
	};
	const static double angleStep;
};
