#include "CameraMovementInputHandler.h"
#include <iostream>

void CameraMovementInputHandler::ProcessInput(const InputEvent& e)
{
	if (e.type == InputEvent::EventType::MOUSE_CLICK)
	{
		const MouseClickEvent& event = static_cast<const MouseClickEvent&>(e);
		this->HandleMouseClickEvent(event);
	}
	else if (e.type == InputEvent::EventType::MOUSE_MOVE)
	{
		const MouseMoveEvent& event = static_cast<const MouseMoveEvent&>(e);
		this->HandleMouseMoveEvent(event);
	}
	else if (e.type == InputEvent::EventType::KEY)
	{
		const KeyEvent& event = static_cast<const KeyEvent&>(e);
		this->HandleKeyEvent(event);
	}
}

void CameraMovementInputHandler::AddSubscriber(std::shared_ptr<CameraSubscriber> subscriber)
{
	this->cameraMoveSubscribers.push_back(subscriber);
}

void CameraMovementInputHandler::HandleMouseClickEvent(const MouseClickEvent& event)
{
	if (event.button == MouseClickEvent::Button::LEFT)
	{
		if (event.action == KeyOrButtonEvent::Action::PRESS)
			this->rotationOn = true;
		else if (event.action == KeyOrButtonEvent::Action::RELEASE)
		{
			this->rotationOn = false;
			this->lastMousePos = std::nullopt;
		}
	}
	else if (event.button == MouseClickEvent::Button::RIGHT)
	{
		if (event.action == KeyOrButtonEvent::Action::PRESS)
			this->translationOn = true;
		else if (event.action == KeyOrButtonEvent::Action::RELEASE)
		{
			this->translationOn = false;
			this->lastMousePos = std::nullopt;
		}
	}
}

void CameraMovementInputHandler::HandleMouseMoveEvent(const MouseMoveEvent& event)
{
	static constexpr float MOUSE_ROTATION_SENSITIVITY = 0.3f;
	static constexpr float MOUSE_TRANSLATION_SENSITIVITY = 0.005f;

	if (rotationOn || translationOn)
	{
		const glm::dvec2 currentMousePos = glm::dvec2(event.xpos, event.ypos);
		if (!this->lastMousePos.has_value())	// first mouse position of a movement needs to be set
			this->lastMousePos = currentMousePos;
		const glm::dvec2 mouseOffset = currentMousePos - this->lastMousePos.value();
		this->lastMousePos = currentMousePos;
		
		if (rotationOn)
		{
			this->camera.RotatePitch(-mouseOffset.y * MOUSE_ROTATION_SENSITIVITY);	// negative Y, because GLFW window origin is left-top
			this->camera.RotateYaw(mouseOffset.x * MOUSE_ROTATION_SENSITIVITY);
		}
		if (translationOn)
		{
			// negative, because we are translating the camera, not scene
			this->camera.Translate(glm::vec3(-(mouseOffset.x * MOUSE_TRANSLATION_SENSITIVITY), 0, -(mouseOffset.y * MOUSE_TRANSLATION_SENSITIVITY)));
		}
		this->NotifySubscribers();
	}
}

void CameraMovementInputHandler::HandleKeyEvent(const KeyEvent& event)
{
	static constexpr float moveStep = 0.05f;
	if (event.action != KeyOrButtonEvent::Action::PRESS && event.action != KeyOrButtonEvent::Action::REPEAT)
		return;

	switch (event.key)
	{
	case GLFW_KEY_W:
		this->camera.Translate(glm::vec3(0.f, 0.f, -moveStep)); break;
	case GLFW_KEY_S:
		this->camera.Translate(glm::vec3(0.f, 0.f, moveStep)); break;
	case GLFW_KEY_A:
		this->camera.Translate(glm::vec3(-moveStep, 0.f, 0.f)); break;
	case GLFW_KEY_D:
		this->camera.Translate(glm::vec3(moveStep, 0.f, 0.f)); break;
	case GLFW_KEY_Q:
		this->camera.Translate(glm::vec3(0.f, -moveStep, 0.f)); break;
	case GLFW_KEY_E:
		this->camera.Translate(glm::vec3(0.f, moveStep, 0.f)); break;
	default:
		break;
	}
}

void CameraMovementInputHandler::NotifySubscribers()
{
	for (auto& subscriber : cameraMoveSubscribers)
	{
		auto shared_sub = subscriber.lock();
		if (shared_sub)
			shared_sub->NotifyCameraMove();
	}
}
