#include "..\..\..\includes\GameEngine0\Graphics\Material.h"
#include "GameEngine0/Game.h"
#include "GameEngine0/Graphics/ShaderProgram.h"
#include "GameEngine0/Graphics/Texture.h"

Material::Material()
{
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr) {
		BaseColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
		SpecularColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
		EmissiveColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
	}
	else {
		BaseColour.TextureV3 = SpecularColour.TextureV3 = EmissiveColour.TextureV3 = nullptr;
	}

	EmissiveColour.MultiplierV3 = Vector3(0.0f);
	Shininess = 0.1f;

}

Material::~Material()
{
	BaseColour.TextureV3 = SpecularColour.TextureV3 = EmissiveColour.TextureV3 = nullptr;
}

void Material::Draw(Shaderptr Shader)
{
	if (BaseColour.TextureV3 != nullptr) {
		BaseColour.TextureV3->ActivateTexture(0);
		Shader->SetInt("ImportMat.TColour", 0);
		BaseColour.TextureV3->BindTexture();
	}
	Shader->SetVector3("ImportMat.MColour", BaseColour.MultiplierV3);

	if (SpecularColour.TextureV3 != nullptr) {
		SpecularColour.TextureV3->ActivateTexture(1);
		Shader->SetInt("ImportMat.TSpecular", 1);
		SpecularColour.TextureV3->BindTexture();
	}
	Shader->SetVector3("ImportMat.MSpecular", SpecularColour.MultiplierV3);

	if (EmissiveColour.TextureV3 != nullptr) {
		EmissiveColour.TextureV3->ActivateTexture(2);
		Shader->SetInt("ImportMat.TEmissive", 2);
		EmissiveColour.TextureV3->BindTexture();
	}
	Shader->SetVector3("ImportMat.MEmissive", EmissiveColour.MultiplierV3);

	Shader->SetFloat("ImportMat.Shininess", Shininess);
}
