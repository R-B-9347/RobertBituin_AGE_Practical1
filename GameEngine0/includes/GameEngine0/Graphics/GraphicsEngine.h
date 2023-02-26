#pragma once

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GameEngine0/CoreMinimal.h"


class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	//Create Window
	bool initGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//show newest frame graphics
	void PresentGraphics();
	//clear old Frame graphics
	void ClearGraphics();

	void Draw();

	SDL_Window* GetWindow() const;

	void CreateVAO(GeometricShapes Shape);

	void CreateShader(VFShaderParams ShaderFilePaths);

private:
	SDL_Window* SdlWindow;
	SDL_GLContext SdlGLContext;
	VAOStack VAOs;
	bool bWireframeMode;
	void HandleWireframeMode(bool ShowbWireframeMode);

	Shaderptr Shader;
};