#pragma once
#include "GameEngine0/CoreMinimal.h"

struct ImportImageData {
	int w = 0;
	int h = 0;
	int channels = 0;
};

class Texture {
public:
	Texture();
	~Texture();

	bool CreateTextureFromFilePath(const char* FilePath);

	GE0uint GetID() const { return TextureID; }

	void BindTexture();
	void ActivateTexture(GE0uint Index);
	void ResetTexture();

	const char* GetFilePath() const { return FilePath; }
private:
	GE0uint TextureID;
	
	const char* FilePath;

};