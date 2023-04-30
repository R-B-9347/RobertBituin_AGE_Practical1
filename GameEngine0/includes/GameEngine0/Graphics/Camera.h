#pragma once
#include "GameEngine0/Math/Transformation.h"
#include "glm/glm.hpp"
#include "GameEngine0/Collisions/Collision.h"


struct STCameraData {
	float speed = 5.0f;
	float FOV = 70.0f;

	float NearClip = 0.01f;
	float Farclip = 1000.0f;

	float LookSense = 0.3f;
};

class Camera {
public:
	Camera();

	void Translate(Vector3 Location);

	void AddMovementInput(Vector3 Direction);

	CTransform GetTransforms() const {return Transform; }
	CDirection GetDirections() const { return Directions; }
	STCameraData GetCameraData() const { return CameraData; }

	glm::mat4 GetViewMatrix() const;

	void RotatePitch(float Amount);
	void RotateYaw(float Amount);

	void ZoomFOV(float Amount);

	void Update();

	CollisionPtr GetCameraCollision() const { return CameraCollision; }

private:
	void UpdateDirectionVectors();

private:
	CTransform Transform;
	CDirection Directions;
	STCameraData CameraData;
	CollisionPtr CameraCollision;
};