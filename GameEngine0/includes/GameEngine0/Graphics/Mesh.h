#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"


class Mesh {
public:
	Mesh();

	~Mesh();

	bool CreateSimpleShape(GeometricShapes Shape, Shaderptr MeshShader, TexturePtrStack MeshTextures);

	void Draw();

	CTransform Transform;

private:
	Shaderptr MeshShader;

	TexturePtrStack MeshTextures;

	VAOptr MeshVAO;
};