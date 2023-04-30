#include"GameEngine0/Graphics/GraphicsEngine.h"
#include "GameEngine0/Graphics/Model.h"
#include"GameEngine0/Graphics/ShaderProgram.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GameEngine0/Graphics/Texture.h"
#include "GameEngine0/Graphics/Material.h"
#include "GameEngine0/Graphics/Camera.h"
#include "GameEngine0/Collisions/Collision.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
	EngineDefaultCam = make_shared<Camera>();

}

GraphicsEngine::~GraphicsEngine()
{
	ModelStack.clear();

	Shader = nullptr;

	TextureStack.clear();

	SDL_DestroyWindow(SdlWindow);

	SDL_GL_DeleteContext(SdlGLContext);

	SDL_Quit;

	cout << "destroy graphics engine.." << endl;
}

bool GraphicsEngine::initGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout << "Failed" << SDL_GetError() << endl;
		return false;
	}	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//fullscreen
	int FullscreenFlag = 0;
	if (bFullscreen) {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	//create Window
	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		WWidth,WHeight,
		FullscreenFlag
	);

	//Window Fail
	if (SdlWindow == nullptr) {
		cout << "Window Fail" << SDL_GetError() << endl;
		return false;
	}

	//add all GL attribute to window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);
	if (SdlGLContext == NULL) {
		cout << "SDL GL COntext Fail" << SDL_GetError() << endl;
		return false;
	}
	//making glew work
	glewExperimental = GL_TRUE;

	const GLenum InitGlew = glewInit();
	if (InitGlew != GLEW_OK) {
		cout << "Glew Fail" << glewGetErrorString(InitGlew) << endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	DefaultEngineTexture = CreateTexture("Game/Textures/Grey.png");
	DefaultEngingeMaterial = make_shared<Material>();

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//background color
	glClearColor(0.2,0.1f,0.2f,1.0f);
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{


	HandleWireframeMode(false);



	for (ModelPtr LModel : ModelStack) {
		LModel->Draw();
	}

}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

ModelPtr GraphicsEngine::CreateSimpleModelShape(GeometricShapes Shape, Shaderptr MeshShader)
{
	ModelPtr NewModel = make_shared<Model>();

	if (!NewModel->CreateSimpleMesh(Shape, MeshShader)) {
		return nullptr;
	}
	
	ModelStack.push_back(NewModel);

	return NewModel;
}

ModelPtr GraphicsEngine::ImportModel(const char* FilePath, Shaderptr Shader)
{
	ModelPtr NewModel = make_shared<Model>();

	if(!NewModel->ImportMeshFromFile(FilePath, Shader)) {
		return nullptr;
	}
	ModelStack.push_back(NewModel);
	return NewModel;
}

Shaderptr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
		Shaderptr NewShader = make_shared<ShaderProgram>();

		NewShader->InitVFShader(ShaderFilePaths);

		Shader = NewShader;

		return NewShader;
}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	for (TexturePtr TestTexture : TextureStack) {
		if (TestTexture->GetFilePath() == FilePath) {
			NewTexture = TestTexture;
			cout << "Found Texture assigning" << endl;
			break;
		}
	}
	if (NewTexture == nullptr) {
		cout << "creating New Texture" << endl;
		NewTexture = make_shared<Texture>();

		if (NewTexture->CreateTextureFromFilePath(FilePath)) {
			cout << NewTexture->GetID() << " success added Texture to stack" << endl;

			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::ApplyScreenTransformations(Shaderptr Shader)
{
	float FOV = EngineDefaultCam->GetCameraData().FOV;
	Vector3 ViewPosition = EngineDefaultCam->GetTransforms().Location;
	
	int WWidth, WHeight = 0;

	SDL_GetWindowSize(SdlWindow, &WWidth, &WHeight);
	float AR = static_cast<float>(WWidth) / static_cast<float>(max(WHeight, 1));
	
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = EngineDefaultCam->GetViewMatrix();
	projection = glm::perspective(glm::radians(FOV), AR, EngineDefaultCam->GetCameraData().NearClip, EngineDefaultCam->GetCameraData().Farclip);

	Shader->SetMat4("view", view);
	Shader->SetMat4("projection", projection);
}

void GraphicsEngine::RemoveModel(ModelPtr ModelToRemove)
{
	ModelPtrStack::iterator ModelIndex = find(ModelStack.begin(),ModelStack.end(), ModelToRemove);

	if (ModelIndex == ModelStack.end())
		return;

	ModelStack.erase(ModelIndex);
}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	if (bShowWireframeMode != bWireframeMode) {
		bWireframeMode = bShowWireframeMode;

		if (bWireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		
		cout << "WireframeMode Updated" << endl;
	}
}
