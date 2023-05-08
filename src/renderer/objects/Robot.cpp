#include "Robot.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

const double Robot::angleStep = 0.01;

Robot::Robot()
{
	for (int i = 0; i < 6; i++)
	{
		std::string filename = "mesh" + std::to_string(i + 1) + ".txt";
		arms[i] = std::make_unique<Arm>(filename);
	}
	//SetArmPosition(glm::vec3(.5f, -.5f, -.5f), glm::vec3(0.f, 0.f, 1.f));
}

void Robot::Render(const Camera& camera) const
{
	for (int i = 0; i < 6; i++)
	{
		arms[i]->Render(camera);
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

void Robot::SetArmPosition(const glm::vec3& pos, const glm::vec3& normal)
{
	float l1 = .91f, l2 = .81f, l3 = .33f, dy = .27f, dz = .26f;
	auto N = glm::normalize(normal);
	//normal.normalize();
	
	glm::vec3 pos1 = pos + normal * l3;
	float e = sqrtf(pos1.z * pos1.z + pos1.x * pos1.x - dz * dz);

	float a1 = atan2(pos1.z, -pos1.x) + atan2(dz, e);
	glm::vec3 pos2(e, pos1.y - dy, .0f);
	float a3 = -acosf(glm::min(1.0f, (pos2.x * pos2.x + pos2.y * pos2.y - l1 * l1 - l2 * l2) / (2.0f * l1 * l2)));
	
	float k = l1 + l2 * cosf(a3), l = l2 * sinf(a3);
	float a2 = -atan2(pos2.y, sqrtf(pos2.x * pos2.x + pos2.z * pos2.z)) - atan2(l, k);
	
	glm::vec3 normal1;
	//normal1 = glm::vec3(RotateRadMatrix44('y', -a1) * glm::vec4(N.x, N.y, N.z, .0f));
	normal1 = glm::rotate(-a1, glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(N, 0.f);
	//normal1 = glm::vec3(RotateRadMatrix44('z', -(a2 + a3)) * glm::vec4(normal1.x, normal1.y, normal1.z, .0f));
	normal1 = glm::rotate(-(a2 + a3), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(normal1, 0.f);
	float a5 = acosf(normal1.x);
	float a4 = atan2(normal1.z, normal1.y);

	angles[0] = a1;
	angles[1] = a2;
	angles[2] = a3;
	angles[3] = a4;
	angles[4] = a5;
	updateArms();
}
