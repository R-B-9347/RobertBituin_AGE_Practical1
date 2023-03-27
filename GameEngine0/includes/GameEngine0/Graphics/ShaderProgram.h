#pragma once
#include "GameEngine0/CoreMinimal.h"
#include "glm/glm.hpp"
class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	//shader initilation
	bool InitVFShader(VFShaderParams ShaderFilePaths);

	void RunShader();

	GE0uint GetID() const { return ProgramID; }

	void SetMat4(const char* ShaderVariable, glm::mat4 Value);

	void SetInt(const char* ShaderVarName, int Value);

private:
	bool AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type);

	bool Link();
private:
	GE0uint ProgramID;
	//Vertex - 0
	//Fragment - 1
	GE0uint VFShaderIDs[2] = { 0 };
};