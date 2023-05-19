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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(false);
	this->particles->Render(*this->camera);
	glDepthMask(true);
	glDisable(GL_BLEND);
}

void Scene::DrawShadowVolumes()
{
	this->robot->DrawShadowVolumes(*this->camera);
	this->metalSheet->DrawShadowVolumes(*this->camera);
	this->cylinder->DrawShadowVolumes(*this->camera);
}

void Scene::DrawSolidColor(std::initializer_list<float> c)
{
	glm::vec4 color(c.begin()[0], c.begin()[1], c.begin()[2], c.begin()[3]);
	this->program->Use();
	this->vao->Unbind();
	this->vao->Bind();
	this->program->SetVec4("color", color);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Scene::SetLight(bool enable)
{
	this->robot->SetLight(enable);
	this->metalSheet->SetLight(enable);
	this->cylinder->SetLight(enable);
	this->roomBox->SetLight(enable);
}

Scene::Scene(unsigned int frame_width, unsigned int frame_height) :
	camera(std::make_shared<Camera>(90, static_cast<float>(frame_width) / static_cast<float>(frame_height), 0.1f, 100.f)),
	cameraMovementHandler(std::make_shared<CameraMovementInputHandler>(*this->camera)),
	floor(std::make_unique<Floor>(50, 50)),
	robot(std::make_unique<Robot>()),
	roomBox(std::make_unique<Box>()),
	metalSheet(std::make_unique<Sheet>(glm::vec3(-1.5f, 0.f, 0.f), glm::radians(30.f))),
	cylinder(std::make_unique<Cylinder>()),
	particles(std::make_unique<ParticlesSystem>(glm::vec3(0.001f, 0.f, 0.f)))
{
	this->camera->Translate(glm::vec3(0.f, 1.f, 1.f));
	this->roomBox->Initialize();
	this->metalSheet->Initialize();
	this->cylinder->Initialize();

	this->robotMovementHandler = std::make_shared<RobotMovementInputHandler>(*this->metalSheet, *this->robot);

	program = ProgramFactory::CreateProgram("pass.vert", "uniform.frag");

	std::vector<float> vertices = {
		// quad spanning the entire screen
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		// second triangle
		-1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f
	};
	this->vao = std::make_unique<GL::VAO>();
	this->vbo = std::make_unique<GL::VBO>(vertices.data(),
		sizeof(float) * vertices.size());
	this->vao->DefineFloatAttribute(*this->vbo, 0, 3,
		GL::VAO::FloatAttribute::FLOAT, 3 * sizeof(float), 0);
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
		if (keyEvent.action == KeyOrButtonEvent::Action::PRESS && keyEvent.key == GLFW_KEY_C)
		{
			this->animationOn = !this->animationOn;
		}
	}
	this->cameraMovementHandler->ProcessInput(inputEvent);
	this->robotMovementHandler->ProcessInput(inputEvent);
}

void Scene::SetFramebufferSize(unsigned int width, unsigned int height)
{
	this->camera->SetAspect(static_cast<float>(width) / static_cast<float>(height));
}

void Scene::Update(double dt)
{
	static float time = 0;

	if (this->animationOn)
	{
		time += dt;

		auto modelMtx = glm::mat4(1.f);
		modelMtx = glm::translate(modelMtx, this->metalSheet->GetCenterPosition());
		modelMtx = glm::rotate(modelMtx, this->metalSheet->GetSlopeAngle(), glm::vec3(0.f, 0.f, 1.f));

		float circleRadius = 0.25f;
		auto pos = glm::vec4(0.f, circleRadius * glm::cos(time), circleRadius * glm::sin(time), 1.f);
		pos = modelMtx * pos;
		auto normal = glm::rotateZ(glm::vec3(1.f, 0.f, 0.f), this->metalSheet->GetSlopeAngle());

		this->robot->SetArmPosition(pos, normal);
		this->particles->Update(dt, pos);
	}
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
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glStencilFunc(GL_NOTEQUAL, 0, ~0);
	SetLight(false);
	Draw();

	glStencilFunc(GL_EQUAL, 0, ~0);
	SetLight(true);
	Draw();
	//DrawShadowVolumes();

	/*glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_EQUAL, 1, ~0);
	DrawSolidColor({ 1.f, 0.f, 0.f, 1.f });

	glStencilFunc(GL_EQUAL, 2, ~0);
	DrawSolidColor({ 1.f, .5f, 0.f, 1.f });

	glStencilFunc(GL_EQUAL, 3, ~0);
	DrawSolidColor({ 1.f, 1.f, 0.f, 1.f });

	glStencilFunc(GL_EQUAL, 4, ~0);
	DrawSolidColor({ 0.f, 1.f, 0.f, 1.f });

	glDisable(GL_STENCIL_TEST);*/

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

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}
