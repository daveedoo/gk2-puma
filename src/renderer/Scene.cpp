#include "Scene.h"
#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>
#include "../gl/wrappers/Shader.h"
#include "../Window/input/handlers/CameraMovementInputHandler.h"
#include "../Window/input/events/ResizeEvent.h"
#include "../Window/input/events/modded/KeyEvent.h"
#include <imgui.h>
#include <glm/gtx/rotate_vector.hpp>
#include <imgui_stdlib.h>
#include <glm/gtc/type_ptr.hpp>
#include "../gl/ProgramFactory.h"


Scene::Scene(unsigned int frame_width, unsigned int frame_height) :
	camera(std::make_shared<Camera>(90, static_cast<float>(frame_width) / static_cast<float>(frame_height), 0.1f, 100.f)),
	cameraMovementHandler(std::make_shared<CameraMovementInputHandler>(*this->camera)),
	floor(std::make_unique<Floor>(50, 50)), robot(std::make_unique<Robot>()), roomBox(std::make_unique<Box>()),
	metalSheet(std::make_unique<Sheet>()), cylinder(std::make_unique<Cylinder>())
{
	this->camera->Translate(glm::vec3(0.f, 1.f, 1.f));
	this->roomBox->Initialize();
	this->metalSheet->Initialize();
	this->cylinder->Initialize();
}

void Scene::HandleEvent(const InputEvent& inputEvent)	// TODO: change event type to be not ResizeEvent (it is handled in SetFramebufferSize())
{
	if (inputEvent.type == InputEvent::EventType::KEY) 
	{
		auto keyEvent = static_cast<const KeyEvent&>(inputEvent);
		if (keyEvent.action == KeyOrButtonEvent::Action::PRESS || keyEvent.action == KeyOrButtonEvent::Action::REPEAT)
		{
			this->robot->HandleKey(keyEvent);
		}
	}
	this->cameraMovementHandler->ProcessInput(inputEvent);
}

void Scene::SetFramebufferSize(unsigned int width, unsigned int height)
{
	this->camera->SetAspect(static_cast<float>(width) / static_cast<float>(height));
}

void Scene::Update()
{
}

void Scene::Render()
{
	glClearColor(bgColor.r, bgColor.g, bgColor.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//this->floor->Render(*this->camera);
	this->robot->Render(*this->camera);
	this->roomBox->Render(*this->camera);
	this->metalSheet->Render(*this->camera);
	this->cylinder->Render(*this->camera);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}
