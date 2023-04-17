#include "..\..\..\includes\GameEngine0\Graphics\Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GameEngine0/Game.h"

Camera::Camera()
{
	UpdateDirectionVectors();
	Transform.Location -= Directions.Forward * 2.0f;
	
}

void Camera::Translate(Vector3 Location)
{
	Transform.Location = Location;

	UpdateDirectionVectors();
}

void Camera::AddMovementInput(Vector3 Direction)
{
	if (glm::length(Direction) == 0)
		return;

	Direction = glm::normalize(Direction);

	Vector3 Vel = Direction * (CameraData.speed * Game::GetGameInstance().GetFDeltaTime());

	Vector3 NewPos = Transform.Location + Vel;

	if (Transform.Location != NewPos) {
		Translate(NewPos);
	}
}

glm::mat4 Camera::GetViewMatrix() const
{

	return glm::lookAt(Transform.Location,Transform.Location + Directions.Forward, Directions.Up);
}

void Camera::RotatePitch(float Amount)
{
	Transform.Rotation.x += Amount * CameraData.LookSense;

	Transform.Rotation.x += Amount;
	if (Transform.Rotation.x > 89.0f)
		Transform.Rotation.x = 89.0f;
	if (Transform.Rotation.x < -89.0f)
		Transform.Rotation.x = -89.0f;
	UpdateDirectionVectors();
}

void Camera::RotateYaw(float Amount)
{
	Transform.Rotation.y += Amount * CameraData.LookSense;

	Transform.Rotation.y += Amount;

	Transform.Rotation.y = glm::mod(Transform.Rotation.y, 360.0f);
}

void Camera::ZoomFOV(float Amount)
{
	STCameraData NewFOV;
		NewFOV.FOV += Amount;
}

void Camera::UpdateDirectionVectors()
{
	Vector3 ForwardDirection;

	ForwardDirection.x = cos(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));

	ForwardDirection.y = sin(glm::radians(Transform.Rotation.x));

	ForwardDirection.z = sin(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));

	ForwardDirection = glm::normalize(ForwardDirection);

	Directions.Forward = ForwardDirection;

	Directions.Right = glm::normalize(glm::cross(Directions.Forward, Vector3(0.0f, 1.0f, 0.0f)));
	Directions.Up = glm::normalize(glm::cross(Directions.Right, Directions.Forward));
}
