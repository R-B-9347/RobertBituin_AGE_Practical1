#pragma once
#include "SDL2/SDL.h"
#include "GameEngine0/CoreMinimal.h"
#include "GameEngine0/Math/Transformation.h"

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

	ModelPtr CreateSimpleModelShape(GeometricShapes Shape, Shaderptr MeshShader);

	ModelPtr ImportModel(const char* FilePath, Shaderptr Shader);

	Shaderptr CreateShader(VFShaderParams ShaderFilePaths);

	TexturePtr CreateTexture(const char* FilePath);

	void ApplyScreenTransformations(Shaderptr Shader);

	CameraPtr EngineDefaultCam;
	float AdjFov;
	TexturePtr DefaultEngineTexture;
	MaterialPtr DefaultEngingeMaterial;

	void RemoveModel(ModelPtr ModelToRemove);

private:
	SDL_Window* SdlWindow;
	SDL_GLContext SdlGLContext;

	bool bWireframeMode;
	void HandleWireframeMode(bool ShowbWireframeMode);

	Shaderptr Shader;

	TexturePtrStack TextureStack;

	ModelPtrStack ModelStack;

};