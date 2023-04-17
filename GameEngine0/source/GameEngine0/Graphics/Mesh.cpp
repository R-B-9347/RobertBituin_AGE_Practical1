#include "..\..\..\includes\GameEngine0\Graphics\Mesh.h"
#include "GameEngine0/Graphics/ShaderProgram.h"
#include "GameEngine0/Graphics/VertexArrayObject.h"
#include "GameEngine0/Graphics/Material.h"
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
	MeshVAO = nullptr;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, Shaderptr MeshShader, GE0uint MaterialSlot)
{
	cout << "creating mesh.." << endl;

	MeshVAO = make_shared<VAO>(Shape);

	if (MeshVAO == nullptr) {
		cout << "mesh failed to be created" << endl;
		return false;
	}

	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh Created Successfully" << endl;

	return true;
}

bool Mesh::CreateMesh(vector<Vertex> Verticies, vector<GE0uint> Indicies, Shaderptr MeshShader, GE0uint MaterialSlot)
{
	cout << "creating mesh.." << endl;

	MeshVAO = make_shared<VAO>(Verticies, Indicies);

	if (MeshVAO == nullptr) {
		cout << "mesh failed to be created" << endl;
		return false;
	}

	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh Created Successfully" << endl;

	return true;
}


void Mesh::Draw(MaterialPtr MeshMaterial)
{
	MeshShader->RunShader();

	if (MeshMaterial != nullptr) {
		MeshMaterial->Draw(MeshShader);
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
