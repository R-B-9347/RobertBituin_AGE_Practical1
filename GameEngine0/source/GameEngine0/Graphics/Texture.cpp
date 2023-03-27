#include "..\..\..\includes\GameEngine0\Graphics\Texture.h"
#include "GL/glew.h"
#include "stb_image/stb_image.h"
#include <string>
Texture::Texture()
{
	TextureID = 0;
	FilePath = " ";

	glGenTextures(1, &TextureID);
	BindTexture();

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	cout << "initialised Texture" << TextureID << endl;
}

Texture::~Texture()
{
	glDeleteTextures(1, &TextureID);
	
	cout << "texture " << TextureID << " Deleted" << endl;
}

bool Texture::CreateTextureFromFilePath(const char* FilePath)
{
	BindTexture();
	this->FilePath = FilePath;

	ImportImageData ImageData;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* RawImage = stbi_load(
		FilePath,
		&ImageData.w, &ImageData.h,
		&ImageData.channels,
		STBI_rgb_alpha
	);
	if (!RawImage) {
		cout << " Textrue Could not be loaded" << endl;
		return false;
	}
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		ImageData.w, ImageData.h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		RawImage
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(RawImage);

	return true;
}

void Texture::BindTexture()
{
	if (TextureID != 0) {
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}
	
}

void Texture::ActivateTexture(GE0uint Index)
{
	if (TextureID != 0) {
		glActiveTexture(GL_TEXTURE0 + Index);
	}
}

void Texture::ResetTexture()
{
	glActiveTexture(GL_TEXTURE0);
}
