#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"
class aiNode;
class aiScene;
class aiMesh;

class Model {
public:
	Model();
	~Model();

	bool CreateSimpleMesh(GeometricShapes Shape,Shaderptr ModelShader);

	void Draw();

	void SetMaterialBySlot(GE0uint SlotIndex,MaterialPtr NewMaterial);

	bool ImportMeshFromFile(const char* ImportFilePath, Shaderptr ModelShader);

	MaterialPtr GetMaterialBySlot(GE0uint SlotIndex) const;

	const char* GetFilePath() const { return ModelFilePath; }

private:
	void FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene);
	MeshPtr ConvertImportMeshToEngineMesh(aiMesh* importMesh, const aiScene* Scene);
public:
	CTransform Transform;

private:
	MeshPtrStack MeshStack;
	MaterialPtrStack MaterialStack;
	Shaderptr ModelShader;
	const char* ModelFilePath;
};