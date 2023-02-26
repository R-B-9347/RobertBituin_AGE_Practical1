#include "GameEngine0/Graphics/ShaderProgram.h"
#include "GL/glew.h"
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"
ShaderProgram::ShaderProgram()
{
	ProgramID = 0;
}

ShaderProgram::~ShaderProgram()
{
	for (GE0uint VFShaderID : VFShaderIDs) {
		glDetachShader(ProgramID, VFShaderID);
		glDeleteShader(VFShaderID);

	}
	glDeleteProgram(ProgramID);

	cout << "Shader Program " << ProgramID << " Has Been Destroyed" << endl;
}

bool ShaderProgram::InitVFShader(VFShaderParams ShaderFilePaths)
{
	ProgramID = glCreateProgram();
	
	if (ProgramID < 1) {
		cout << "Shader Program| No Program ID" << endl;
		return false;
	}

	bool VShader = AttachShader(ShaderFilePaths.VertexShaderPath, ShaderTypes::Vertex);
	bool FShader = AttachShader(ShaderFilePaths.FragmentShaderPath, ShaderTypes::Fragment);

	if (!VShader || !FShader) {
		return false;
	}

	return Link();
}

void ShaderProgram::RunShader()
{
	glUseProgram(ProgramID);
}

void ShaderProgram::SetMat4(const char* ShaderVariable, glm::mat4 Value)
{
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, ShaderVariable), 1, GL_FALSE, value_ptr(Value));
}

bool ShaderProgram::AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type)
{
	string ShaderCode;
	ifstream FilePathStream(ShaderFilePath);
	if (!FilePathStream.is_open()) {
		wclog << "Shader Program | " << ShaderFilePath << "not Found" << endl;
		return false;
	}
	stringstream RawShaderCode;
	RawShaderCode << FilePathStream.rdbuf();
	ShaderCode = RawShaderCode.str();
	
	FilePathStream.close();

	GE0uint ShaderID = 0;

	switch (Type)
	{
	case ShaderTypes::Vertex:
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		VFShaderIDs[0] = ShaderID;
		break;
	case ShaderTypes::Fragment:
		ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		VFShaderIDs[1] = ShaderID;
		break;
	default:
		break;
	}

	const char* ShaderCodePtr = ShaderCode.c_str();
	
	glShaderSource(ShaderID, 1, &ShaderCodePtr, NULL);

	glCompileShader(ShaderID);

	int LogLength = 0;
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogLength);

	if (LogLength > 0) {
		vector<char> LogMessage(LogLength + 1);
		glGetShaderInfoLog(ShaderID, LogLength, NULL, &LogMessage[0]);

		int CompileStatus = GL_TRUE;

		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &CompileStatus);
		if (CompileStatus == GL_TRUE) {
			wclog << "Shader Compiler | " << ShaderFilePath << "Compile success " << endl << &LogMessage[0] << endl;
		}
		else {
			wclog << "Shader Compiler | " << ShaderFilePath << "Compile Failed " << endl << &LogMessage[0] << endl;
			return false;
		}
	}
	else {
		wclog << "Shader Program | " << ShaderFilePath << "Compiled Success no logs" << endl;
	}
	glAttachShader(ProgramID, ShaderID);

	
	return true;
}

bool ShaderProgram::Link()
{
	glLinkProgram(ProgramID);

	int LogLength = 0;
	glGetShaderiv(ProgramID, GL_INFO_LOG_LENGTH, &LogLength);

	if (LogLength > 0) {
		vector<char> LogMessage(LogLength + 1);
		glGetShaderInfoLog(ProgramID, LogLength, NULL, &LogMessage[0]);

		int CompileStatus = GL_TRUE;
		glGetShaderiv(ProgramID, GL_COMPILE_STATUS, &CompileStatus);

		if (CompileStatus == GL_TRUE) {
			wclog << "Shader Program | Link success " << endl << &LogMessage[0] << endl;
		}
		else {
			wclog << "Shader Program | Link Fail " << endl << &LogMessage[0] << endl;
			return false;
		}
	}
	else {
		wclog << "Shader Program | Link Success no logs " << endl;
	}
	return true;
}
