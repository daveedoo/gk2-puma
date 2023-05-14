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


void Scene::Draw()
{
	//this->floor->Render(*this->camera);
	this->robot->Render(*this->camera);
	this->roomBox->Render(*this->camera);
	this->metalSheet->Render(*this->camera);
	this->cylinder->Render(*this->camera);
}

void Scene::DrawShadowVolumes()
{
	this->robot->DrawShadowVolumes(*this->camera);
	this->metalSheet->DrawShadowVolumes(*this->camera);
	this->cylinder->DrawShadowVolumes(*this->camera);
}

void Scene::SetLight(bool enable)
{
	//TODO
}

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

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	Draw();

	glEnable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_ALWAYS, 0, ~0);

	glCullFace(GL_BACK);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	DrawShadowVolumes();

	glCullFace(GL_FRONT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	DrawShadowVolumes();

	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glCullFace(GL_BACK);
	glDepthFunc(GL_GEQUAL);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glStencilFunc(GL_GREATER, 0, ~0);
	SetLight(false);
	Draw();

	glStencilFunc(GL_EQUAL, 0, ~0);
	SetLight(true);
	Draw();

	glDisable(GL_STENCIL_TEST);

	/*glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_CULL_FACE);
	glEnable(GL_STENCIL_TEST);
	glDepthMask(GL_FALSE);

	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_INCR_WRAP_EXT);
	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_DECR_WRAP_EXT);

	glStencilFuncSeparate(GL_FRONT_AND_BACK, GL_ALWAYS, 0, ~0);

	DrawShadowVolumes();*/

	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
}
