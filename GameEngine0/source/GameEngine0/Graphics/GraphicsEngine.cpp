#include"GameEngine0/Graphics/GraphicsEngine.h"
#include"GameEngine0/Graphics/VertexArrayObject.h"
#include"GameEngine0/Graphics/ShaderProgram.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	
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
	return true;
}

void GraphicsEngine::PresentGraphics()
{
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//background color
	glClearColor(0.255,0.192f,0.203f,1.0f);
	//clear screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireframeMode(false);
	GE0uint index = 0;
	for (VAOptr VAO : VAOs) {
		Shader->RunShader();

		glm::mat4 transform = glm::mat4(1.0f);

		//Triangle
		if (index == 0) {
			transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 0.0f));
			transform = glm::scale(transform, glm::vec3(0.4f, 0.4f, 1.0f));
		}
		//Square
		else if (index == 1) {
			transform = glm::translate(transform, glm::vec3(-0.6f, 0.5f, 0.0f));

			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

			transform = glm::scale(transform, glm::vec3(0.5f,0.5f,1.0f));
		}
		//Circle (rupies)
		else if (index == 2) {
			transform = glm::translate(transform, glm::vec3(-0.5f, -0.5f, 0.0f));
			transform = glm::scale(transform, glm::vec3(0.7f, 0.7f, 1.0f));
		}


		Shader->SetMat4("transform", transform);

		VAO->Draw();
		index++;
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

void GraphicsEngine::CreateVAO(GeometricShapes Shape)
{
	VAOptr NewVAO = make_shared<VAO>(Shape);

	VAOs.push_back(NewVAO);
}

void GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	Shaderptr NewShader = make_shared<ShaderProgram>();

	NewShader->InitVFShader(ShaderFilePaths);

	Shader = NewShader;
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
