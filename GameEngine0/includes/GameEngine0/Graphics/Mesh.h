#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"

struct Vertex;

class Mesh {
public:
	Mesh();

	~Mesh();

	bool CreateSimpleShape(GeometricShapes Shape, Shaderptr MeshShader, GE0uint MaterialSlot);

	bool CreateMesh(vector<Vertex> Verticies, vector<GE0uint> Indicies, Shaderptr MeshShader, GE0uint MaterialSlot);

	void Draw(MaterialPtr MeshMaterial);

	GE0uint GetMaterialSlot() const { return MaterialSlot;}

public:
	CTransform Transform;

private:
	Shaderptr MeshShader;

	GE0uint MaterialSlot;

	VAOptr MeshVAO;

	
};