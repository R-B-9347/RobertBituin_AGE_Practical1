#include "..\..\..\includes\GameEngine0\Graphics\Mesh.h"
#include "GameEngine0/Graphics/ShaderProgram.h"
#include "GameEngine0/Graphics/VertexArrayObject.h"
#include "GameEngine0/Graphics/Texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GameEngine0/Game.h"
#include "GameEngine0/Graphics/GraphicsEngine.h"

Mesh::Mesh()
{
	cout << "initialised mesh" << endl;

}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshTextures.clear();
	MeshVAO = nullptr;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, Shaderptr MeshShader, TexturePtrStack MeshTextures)
{
	cout << "creating mesh.." << endl;

	MeshVAO = make_shared<VAO>(Shape);

	if (MeshVAO == nullptr) {
		cout << "mesh failed to be created" << endl;
		return false;
	}

	this->MeshShader = MeshShader;
	this->MeshTextures = MeshTextures;

	cout << "Mesh Created Successfully" << endl;

	return true;
}

void Mesh::Draw()
{
	MeshShader->RunShader();

	for (GE0uint Index = 0; Index < MeshTextures.size(); Index++) {
		MeshTextures[Index]->ActivateTexture(Index);
		MeshShader->SetInt("TextureColour", Index);
		MeshTextures[Index]->BindTexture();
	}

	static CTransform OldTransform;
	if (Transform != OldTransform) {
		OldTransform = Transform;

		glm::mat4 MatTransform = glm::mat4(1.0f);

		//Translate Rotate Scale
		MatTransform = glm::translate(MatTransform, Transform.Location);

		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.x), Vector3(1.0f,0.0f,0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3(0.0f, 0.0f, 1.0f));

		MatTransform = glm::scale(MatTransform, Transform.Scale);

		MeshShader->SetMat4("model", MatTransform);
	}

	Game::GetGameInstance().GetGraphicsEngine()->ApplyScreenTransformations(MeshShader);
	MeshVAO->Draw();
}
