#include "GameEngine0/Collisions/Collision.h"
#include "GameEngine0/Graphics/ShaderProgram.h"
#include "GameEngine0/Graphics/Mesh.h"
#include "GameEngine0/Graphics/Material.h"
#include "GL/glew.h"

Collision::Collision(Vector3 Location, Vector3 Offset)
{
	Transform.Location = Location;
	this->Offset = Offset;
	DebugMesh = nullptr;
	DebugShader = nullptr;

	cout << "Creating Collision" << endl;
}

Collision::~Collision()
{
	DebugMesh = nullptr;
	DebugShader = nullptr;

	cout << "Destroyed Collision" << endl;
}

BoxCollision::BoxCollision(Vector3 Location, Vector3 Offset, Vector3 Dimensions) : Collision(Location, Offset)
{
	this->Dimensions = Dimensions;

	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}

bool BoxCollision::IsOverLapping(Collision& OtherCol)
{
	const BoxCollision& OtherBox = dynamic_cast<BoxCollision&>(OtherCol);

	return(
		OtherBox.Min.x <= Max.x &&
		OtherBox.Max.x >= Min.x &&
		OtherBox.Min.y <= Max.y &&
		OtherBox.Max.y >= Min.y &&
		OtherBox.Min.z <= Max.z &&
		OtherBox.Max.z >= Min.z
		);

}

Vector3 BoxCollision::FindCenter()
{
	return Transform.Location + Offset;
}

void BoxCollision::DebugDraw(Vector3 Colour)
{
	if (DebugMesh == nullptr) {
		DebugShader = make_shared<ShaderProgram>();
		DebugShader->InitVFShader({
			L"Game/Shaders/WireFrameShader/WireFrameShader.svert",
			L"Game/Shaders/WireFrameShader/WireframeShader.sfrag"
			});
		DebugMesh = make_shared<Mesh>();
		if (!DebugMesh->CreateSimpleShape(GeometricShapes::Cube, DebugShader, 0)) {
			DebugMesh = nullptr;
			DebugShader = nullptr;
			return;
		}
		DebugMaterial = make_shared<Material>();
		DebugMaterial->BaseColour.TextureV3 = nullptr;
		DebugMaterial->SpecularColour.TextureV3 = nullptr;
		DebugMaterial->EmissiveColour.TextureV3 = nullptr;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DebugMesh->Transform.Location = FindCenter();
	DebugMesh->Transform.Rotation = Transform.Rotation;
	DebugMesh->Transform.Scale = Dimensions;

	DebugMesh->Draw(DebugMaterial);

	DebugShader->RunShader();
	DebugShader->SetVector3("InColour", Colour);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoxCollision::SetLocation(Vector3 NewLocation)
{
	Collision::SetLocation(NewLocation);

	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}

void BoxCollision::SetDimensions(Vector3 NewDimensions)
{
	Dimensions = NewDimensions;

	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}
