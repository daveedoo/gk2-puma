#pragma once
#include <glm/glm.hpp>

class Camera
{
private:
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 translation = glm::vec3(0.f, 0.f, 0.f);

	// RPY angles of camera *direction*
	static constexpr float YAW_ZERO = -90.f;	// defualt camera looking direction is (0, 0, -1)
	float pitch = 0.f;
	float yaw = YAW_ZERO;

	void UpdateViewMatrix();

	float fov = 50;
	float near = 0.1f;
	float far = 100.f;
	float aspect;
	void UpdatePerspective();

public:
	Camera(float fov, float aspect, float near, float far);

	glm::mat4 GetViewMatrix() const { return this->view; }
	glm::mat4 GetProjectionMatrix() const { return this->projection; }

	/// Rotations around Y axis in degrees
	void RotateYaw(float angle);
	/// Rotations between the poles in degrees
	void RotatePitch(float angle);
	void Translate(glm::vec3 vector);

	//void SetOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
	/// <param name="fov">Field of view in degrees</param>
	void SetPerspectiveProjection(float fov, float aspect, float near, float far);
	void SetFov(float fov);
	void SetAspect(float aspect);
	void SetNear(float near);
	void SetFar(float far);
};
