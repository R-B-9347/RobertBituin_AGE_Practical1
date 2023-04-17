#include "..\..\..\includes\GameEngine0\Graphics\Model.h"
#include "GameEngine0/Graphics/Mesh.h"
#include "GameEngine0/Game.h"
#include"GameEngine0/Graphics/Vertex.h"

#include"assimp/Importer.hpp"
#include"assimp/scene.h"
#include"assimp/postprocess.h"

Model::Model()
{
	ModelFilePath = "";
}

Model::~Model()
{
	MeshStack.clear();
	MaterialStack.clear();
	ModelShader = nullptr;
}

bool Model::CreateSimpleMesh(GeometricShapes Shape, Shaderptr ModelShader)
{
	MeshPtr NewMesh = make_shared<Mesh>();

	if (NewMesh->CreateSimpleShape(Shape, ModelShader, 0))
		 ;

	MeshStack.clear();
	MaterialStack.clear();
	this->ModelShader = ModelShader;

	MaterialStack.push_back(Game::GetGameInstance().GetDefuaultEngineMaterial());

	MeshStack.push_back(NewMesh);

	return true;
}

void Model::Draw()
{
	for (MeshPtr LMesh : MeshStack) {
		LMesh->Transform = this->Transform;

		LMesh->Draw(MaterialStack[LMesh->GetMaterialSlot()]);

	}
}

void Model::SetMaterialBySlot(GE0uint SlotIndex, MaterialPtr NewMaterial)
{
	if (MaterialStack.size() <= SlotIndex) {
		cout << "Model | No Material Slot Exist of that Index " << SlotIndex << endl;
		return;
	}
	MaterialStack[SlotIndex] = NewMaterial;
}

bool Model::ImportMeshFromFile(const char* ImportFilePath, Shaderptr ModelShader)
{
	Assimp::Importer Importer;

	const aiScene* Scene = Importer.ReadFile(ImportFilePath, aiProcess_Triangulate);

	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
		cout << "MOdel| Error Import File Path " << ImportFilePath << " - " << Importer.GetErrorString() << endl;
	}
	this->ModelShader = ModelShader;
	ModelFilePath = ImportFilePath;

	FindAndImportSceneMeshes(Scene->mRootNode, Scene);

	for (GE0uint i = 0; i < MaterialStack.size(); i ++ ) {
		MaterialStack[i] = Game::GetGameInstance().GetDefuaultEngineMaterial();
	}

	return true;
}

MaterialPtr Model::GetMaterialBySlot(GE0uint SlotIndex) const
{
	if (MaterialStack.size() <= SlotIndex) {
		cout << "Model | No Material Slot Exist of that Index " << SlotIndex << endl;
		return nullptr;
	}
	return MaterialStack[SlotIndex];
}

void Model::FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene)
{
	for (GE0uint i = 0; i < Node->mNumMeshes; i++) {
		aiMesh* ImpMesh = Scene->mMeshes[Node->mMeshes[i]];

		MeshPtr ConvertedMesh = ConvertImportMeshToEngineMesh(ImpMesh, Scene);
		if (ConvertedMesh != nullptr)
			MeshStack.push_back(ConvertedMesh);
	}

	for (GE0uint i = 0; i < Node->mNumChildren; i++) {
		FindAndImportSceneMeshes(Node->mChildren[i], Scene);
	}
}

MeshPtr Model::ConvertImportMeshToEngineMesh(aiMesh* importMesh, const aiScene* Scene)
{
	vector<Vertex> Verticies;
	vector<GE0uint>Indicies;

	for (GE0uint i = 0; i < importMesh->mNumVertices; i++) {
		Vertex LVertex;
		LVertex.Poistion = Vector3(importMesh->mVertices[i].x, importMesh->mVertices[i].y, importMesh->mVertices[i].z);
		LVertex.Normal = Vector3(importMesh->mNormals[i].x, importMesh->mNormals[i].y, importMesh->mNormals[i].z);
		LVertex.TextCoord = Vector2(importMesh->mTextureCoords[0][i].x, importMesh->mTextureCoords[0][i].y);

		Verticies.push_back(LVertex);
	}

	if (Verticies.size() < 3) {
		cout << "Model| One Model Has no verticies at " << ModelFilePath << endl;
	}

	for (GE0uint i = 0; i < importMesh->mNumFaces; i++) {
		aiFace Face = importMesh->mFaces[i];
		for (GE0uint j = 0; j < Face.mNumIndices; j++) {
			Indicies.push_back(Face.mIndices[j]);
		}
	}

	GE0uint MaterialIndex = importMesh->mMaterialIndex;

	if (MaterialStack.size() < MaterialIndex + 1) {
		MaterialStack.resize(MaterialIndex + 1);
	}

	MeshPtr ConvertedMesh = make_shared<Mesh>();

	ConvertedMesh->CreateMesh(Verticies, Indicies, ModelShader, MaterialIndex);

	return ConvertedMesh;
}
