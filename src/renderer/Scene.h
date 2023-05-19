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
#include "../Window/input/handlers/RobotMovementInputHandler.h"

class Scene
{
private:
	const GLfloat SelectedObjectCursor_LineWidth = 2.f;
	const float SelectedObjectCursor_LineLength = 0.5f;
	const glm::vec3 bgColor = glm::vec3(0.2f, 0.2f, 0.4f);

	std::shared_ptr<Camera> camera;
	std::shared_ptr<CameraMovementInputHandler> cameraMovementHandler;
	std::shared_ptr<RobotMovementInputHandler> robotMovementHandler;
	std::unique_ptr<Floor> floor;
	std::unique_ptr<Robot> robot;
	std::unique_ptr<Box> roomBox;
	std::unique_ptr<Sheet> metalSheet;
	std::unique_ptr<Cylinder> cylinder;

	void Draw();
	void DrawShadowVolumes();
	void SetLight(bool enable);

	void DrawSolidColor(std::initializer_list<float> c);
	std::unique_ptr<GL::VAO> vao;
	std::unique_ptr<GL::VBO> vbo;
	std::unique_ptr<GL::Program> program;
public:
	Scene(unsigned int frame_width, unsigned int frame_height);

	void Update(double dt);
	void Render();

	void HandleEvent(const InputEvent& inputEvent);
	bool IsSceneMoving() const { return cameraMovementHandler->IsCameraMoving(); }
	void SetFramebufferSize(unsigned int width, unsigned int height);
};
