#include "Robot.h"
#include <glm/gtc/matrix_transform.hpp>
const double Robot::angleStep = 0.01;

Robot::Robot()
{
	for (int i = 0; i < 6; i++)
	{
		std::string filename = "mesh" + std::to_string(i + 1) + ".txt";
		arms[i] = std::make_unique<Arm>(filename);
		arms[i]->Initialize();
	}
}

void Robot::Render(const Camera& camera) const
{
	for (int i = 0; i < 6; i++)
	{
		arms[i]->Render(camera);
	}
}

void Robot::DrawShadowVolumes(const Camera& camera) const
{
	for (int i = 0; i < 6; i++)
	{
		arms[i]->DrawShadowVolumes(camera);
	}
}

bool Robot::HandleKey(const KeyEvent& keyEvent)
{
	double angleStep = keyEvent.mods.IsShiftDown() ? 10 * this->angleStep : this->angleStep;
	switch (keyEvent.key) {
	case GLFW_KEY_R:
		angles[0] += angleStep;
		break;
	case GLFW_KEY_F:
		angles[0] -= angleStep;
		break;
	case GLFW_KEY_T:
		angles[1] += angleStep;
		break;
	case GLFW_KEY_G:
		angles[1] -= angleStep;
		break;
	case GLFW_KEY_Y:
		angles[2] += angleStep;
		break;
	case GLFW_KEY_H:
		angles[2] -= angleStep;
		break;
	case GLFW_KEY_U:
		angles[3] += angleStep;
		break;
	case GLFW_KEY_J:
		angles[3] -= angleStep;
		break;
	case GLFW_KEY_I:
		angles[4] += angleStep;
		break;
	case GLFW_KEY_K:
		angles[4] -= angleStep;
		break;
	default:
		return false;
	}
	updateArms();
	return true;
}

void Robot::updateArms()
{
	glm::mat4 model(1.0f);
	model = glm::rotate(model, angles[0], glm::vec3(0.f, 1.f, 0.f));
	arms[1]->SetModel(model);
	model = glm::translate(model, glm::vec3(0.f, .27f, 0.f));
	model = glm::rotate(model, -angles[1], glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(0.f, -.27f, 0.f));
	arms[2]->SetModel(model);
	model = glm::translate(model, glm::vec3(-.91f, .27f, 0.f));
	model = glm::rotate(model, -angles[2], glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(.91f, -.27f, 0.f));
	arms[3]->SetModel(model);
	model = glm::translate(model, glm::vec3(0.f, .27f, -.26f));
	model = glm::rotate(model, angles[3], glm::vec3(1.f, 0.f, 0.f));
	model = glm::translate(model, glm::vec3(0.f, -.27f, .26f));
	arms[4]->SetModel(model);
	model = glm::translate(model, glm::vec3(-1.72f, .27f, 0.f));
	model = glm::rotate(model, -angles[4], glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(1.72f, -.27f, 0.f));
	arms[5]->SetModel(model);
}
