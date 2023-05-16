#include "RobotMovementInputHandler.h"

RobotMovementInputHandler::RobotMovementInputHandler(const Sheet& sheet, Robot& robot)
	: sheet(sheet), robot(robot)
{ }

void RobotMovementInputHandler::ProcessInput(const InputEvent& event)
{
	if (event.type == InputEvent::EventType::KEY)
	{
		const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event);

		if (keyEvent.key == GLFW_KEY_C && keyEvent.action == KeyOrButtonEvent::Action::PRESS)
		{
			if (animationOn)
				robot.StopAnimation();
			else
				robot.StartAnimation(sheet.GetCenterPosition(), 0.25f, sheet.GetSlopeAngle());
			animationOn = !animationOn;
		}
	}
}
