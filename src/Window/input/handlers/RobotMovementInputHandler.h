#pragma once
#include "InputHandler.h"
#include "../../../renderer/objects/Sheet.h"
#include "../../../renderer/objects/Robot.h"

class RobotMovementInputHandler : public InputHandler
{
private:
	const Sheet& sheet;
	Robot& robot;
	bool animationOn = false;

public:
	RobotMovementInputHandler(const Sheet& sheet, Robot& robot);
	virtual void ProcessInput(const InputEvent& event) override;
};

