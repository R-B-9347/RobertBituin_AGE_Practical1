#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"

struct Vec3Texture {
	TexturePtr TextureV3;
	Vector3 MultiplierV3 = Vector3(1.0f);
};

class Material {
public:
	Material();
	~Material();

	void Draw(Shaderptr Shader);


	Vec3Texture BaseColour;
	Vec3Texture SpecularColour;
	Vec3Texture EmissiveColour;

	float Shininess;
};