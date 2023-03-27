#pragma once

#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"
#include "GameEngine0/Graphics/Camera.h"

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

	MeshPtr CreateSimpleMeshShape(GeometricShapes Shape, Shaderptr MeshShader, TexturePtrStack MeshTextures);

	Shaderptr CreateShader(VFShaderParams ShaderFilePaths);

	TexturePtr CreateTexture(const char* FilePath);

	void ApplyScreenTransformations(Shaderptr Shader);

	CameraPtr EngineDefaultCam;
	float AdjFov;
private:
	SDL_Window* SdlWindow;
	SDL_GLContext SdlGLContext;

	bool bWireframeMode;
	void HandleWireframeMode(bool ShowbWireframeMode);

	Shaderptr Shader;

	TexturePtrStack TextureStack;

	MeshPtrStack MeshStack;
};