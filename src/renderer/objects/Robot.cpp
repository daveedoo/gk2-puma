#include "Robot.h"

Robot::Robot()
{
	for (int i = 0; i < 6; i++)
	{
		std::string filename = "mesh" + std::to_string(i + 1) + ".txt";
		arms[i] = std::make_unique<Arm>(filename);
	}
}

void Robot::Render(const Camera& camera) const
{
	for (int i = 0; i < 6; i++)
	{
		arms[i]->Render(camera);
	}
}
