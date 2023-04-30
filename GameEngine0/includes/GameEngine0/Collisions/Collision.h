#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"

class Collision {
public:
	Collision(Vector3 Location, Vector3 Offset);
	~Collision();

	virtual bool IsOverLapping(Collision& OtherCol) { return false; }

	virtual Vector3 FindCenter() { return Vector3(0.0f); }

	virtual void DebugDraw(Vector3 Colour) {}

	virtual void SetLocation(Vector3 NewLocation) { Transform.Location = NewLocation; }

	virtual void SetOffset(Vector3 NewOffset) { Offset = NewOffset; }

	virtual void SetRotation(Vector3 NewRotation) { Transform.Rotation = NewRotation; }

	virtual void SetRotationX(float Value) { Transform.Rotation.x = Value; }
	virtual void SetRotationY(float Value) { Transform.Rotation.y = Value; }
	virtual void SetRotationZ(float Value) { Transform.Rotation.z = Value; }
protected:
	CTransform Transform;
	Vector3 Offset;
	MeshPtr DebugMesh;
	Shaderptr DebugShader;
	MaterialPtr DebugMaterial;
};

class BoxCollision :
	public Collision {
public:
	BoxCollision(Vector3 Location, Vector3 Offset, Vector3 Dimensions);

	bool IsOverLapping(Collision& OtherCol) override;
	Vector3 FindCenter() override;
	void DebugDraw(Vector3 Colour) override;
	void SetLocation(Vector3 NewLocation) override;

	Vector3 GetDimensions() const { return Dimensions; }

	void SetDimensions(Vector3 NewDimensions);
protected:
	Vector3 Dimensions;

	Vector3 Min;
	Vector3 Max;

};