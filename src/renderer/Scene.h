#pragma once
#include <memory>
#include "../gl/wrappers/Program.h"
#include "../gl/wrappers/VAO.h"
#include "../Camera.h"
#include "../Window/input/handlers/CameraMovementInputHandler.h"
#include "objects/Floor.h"
#include "objects/Robot.h"
#include "objects/Box.h"
#include "objects/Sheet.h"
#include "objects/Cylinder.h"

class Scene
{
private:
	const GLfloat SelectedObjectCursor_LineWidth = 2.f;
	const float SelectedObjectCursor_LineLength = 0.5f;
	const glm::vec3 bgColor = glm::vec3(0.2f, 0.2f, 0.4f);

	std::shared_ptr<Camera> camera;
	std::shared_ptr<CameraMovementInputHandler> cameraMovementHandler;
	std::unique_ptr<Floor> floor;
	std::unique_ptr<Robot> robot;
	std::unique_ptr<Box> roomBox;
	std::unique_ptr<Sheet> metalSheet;
	std::unique_ptr<Cylinder> cylinder;

public:
	Scene(unsigned int frame_width, unsigned int frame_height);

	void Update();
	void Render();

	void HandleEvent(const InputEvent& inputEvent);
	bool IsSceneMoving() const { return cameraMovementHandler->IsCameraMoving(); }
	void SetFramebufferSize(unsigned int width, unsigned int height);
};
