#include "GameEngine0\Game.h"
#include "GameEngine0/Graphics/GraphicsEngine.h"
#include "GameEngine0/Graphics/Texture.h"
#include "GameEngine0/Graphics/Mesh.h"
#include "GameEngine0/Input.h"
#include "GameEngine0/Graphics/Camera.h"

Game& Game::GetGameInstance()
{
	static Game* GameInstance = new Game();
	return* GameInstance;
	
}

void Game::DestroyGameInstance()
{
	static Game* GameInstance = &GetGameInstance();

	delete GameInstance;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	//Load window using graphic class
	Graphics = make_shared<GraphicsEngine>();

	if (!Graphics->initGE(WTitle, bFullscreen, WWidth, WHeight)) {
		bIsGameOver = true;
	}
	Run();
}

Game::Game()
{
	cout << "Game Initialized" << endl;
	Graphics = nullptr;
	bIsGameOver = false;
	DefaultTexture = nullptr;
	
}

Game::~Game()
{
	Graphics = nullptr;
	cout << "Game Over" << endl;
}

void Game::Run()
{
	if (!bIsGameOver) {
		GameInput = new Input();
		Shaderptr TextureShader = Graphics->CreateShader({
			L"Game/Shaders/TextureShader/TextureShader.svert",
			L"Game/Shaders/TextureShader/TextureShader.sfrag"
			});

		TexturePtr TGrey = Graphics->CreateTexture("Game/Textures/GreySquare.jpg");
		TexturePtr TColor = Graphics->CreateTexture("Game/Textures/ColourSquare.jpg");

		Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TGrey , TColor });
		
	}
	while (!bIsGameOver) {

		ProcessInpout();

		Update();

		Draw();
	}

	CloseGame();
}

void Game::ProcessInpout()
{
	GameInput->ProcessInput();
}

void Game::Update()
{
	static double LastFrameTime = 0.0;
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	DeltaTime = NewDeltaTime / 1000.0;
	LastFrameTime = CurrentFrameTime;

	Poly->Transform.Rotation.x += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.y += 50.0f * GetFDeltaTime();
	Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();

	Vector3 CameraInput = Vector3(0.0f);
	CDirection CamDirection = Graphics->EngineDefaultCam->GetDirections();
	
	
	if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
		CameraInput += CamDirection.Forward;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
		CameraInput += -CamDirection.Right;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
		CameraInput += -CamDirection.Forward;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
		CameraInput += CamDirection.Right;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_Q)) {
		CameraInput += -CamDirection.Up;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
		CameraInput += CamDirection.Up;
	}
	if (GameInput->IsKeyDown(SDL_SCANCODE_T)) {
		CameraInput += CamDirection.Up;
	}

	CameraInput *= 1.0f * GetFDeltaTime();
	Vector3 NewLocation = Graphics->EngineDefaultCam->GetTransforms().Location += CameraInput;
	Graphics->EngineDefaultCam->Translate(NewLocation);

	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
		cout << "left Mouse Button Down" << endl;
		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime() * 50.0f);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime() * 50.0f);
	}
	if (GameInput->IsMouseButtonDown(MouseButtons::LEFT)) {
		cout << "left Mouse Button Down" << endl;
		Graphics->EngineDefaultCam->ZoomFOV(10.0f);
	}
}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{
	delete GameInput;
}
