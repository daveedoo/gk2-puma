#pragma once
#include "Arm.h"
#include <array>
#include "../../Window/input/events/modded/KeyEvent.h"

class Robot
{
public:
	Robot();
	void Render(const Camera& camera) const;
	void DrawShadowVolumes(const Camera& camera) const;
	bool HandleKey(const KeyEvent& keyEvent);
	void SetLight(bool enable);
private:
	void updateArms();
	std::array<std::unique_ptr<Arm>, 6> arms;
	std::array<float, 5> angles = {
		0.f, 0.f, 0.f, 0.f, 0.f
	};
	const static double angleStep;
};

