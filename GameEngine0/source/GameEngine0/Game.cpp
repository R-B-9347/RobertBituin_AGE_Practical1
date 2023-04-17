#include "GameEngine0\Game.h"
#include "GameEngine0/Graphics/GraphicsEngine.h"
#include "GameEngine0/Graphics/Model.h"
#include "GameEngine0/Input.h"
#include "GameEngine0/Graphics/Camera.h"
#include "GameEngine0/Graphics/Material.h"


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

TexturePtr Game::GetDefaultEngineTexture()
{
	return Graphics->DefaultEngineTexture;
}

MaterialPtr Game::GetDefuaultEngineMaterial()
{
	return Graphics->DefaultEngingeMaterial;
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

		MaterialPtr MGrey = make_shared<Material>();
		MaterialPtr MGrid = make_shared<Material>();

		MGrey->BaseColour.TextureV3 = TGrey;
		MGrid->BaseColour.TextureV3 = TColor;

		Poly = Graphics->ImportModel("Game/Models/Primitives/Cube.fbx", TextureShader);
		Poly1 = Graphics->ImportModel("Game/Models/Primitives/Sphere.fbx", TextureShader);

		Poly->SetMaterialBySlot(0, MGrey);
		Poly1->SetMaterialBySlot(0, MGrid);

		Poly->Transform.Location = Vector3(0.0f, 0.0f, 1.0f);
		Poly1->Transform.Location = Vector3(0.0f, 0.0f, -1.0f);

		Wall = Graphics->ImportModel("Game/Models/DamageWall/source/SM_Wall_Damaged_2x1_A.obj", TextureShader);
		Wall->Transform.Scale = Vector3(0.03f);
		Wall->Transform.Rotation.x = 90.0f;
		Wall->Transform.Location = Vector3(0.0f, -2.0f, 0.0f);

		TexturePtr TWall = Graphics->CreateTexture("Game/Models/DamageWall/textures/T_Wall_Damaged_2x1_A_BC.png");
		MaterialPtr MWall = make_shared<Material>();
		MWall->BaseColour.TextureV3 = TWall;
		Wall->SetMaterialBySlot(1, MWall);

		Pillar = Graphics->ImportModel("Game/Models/MedPillar/source/pillars_low/pillars_low.fbx", TextureShader);
		Pillar->Transform.Scale = Vector3(0.003f);
		Pillar->Transform.Rotation.x = 90.0f;
		Pillar->Transform.Location = Vector3(0.0f, 2.0f, 0.0f);

		TexturePtr TPillar = Graphics->CreateTexture("Game/Models/MedPillar/source/pillars_low/textures/pillars_low_stone rooff.001_BaseColor.1001.jpg");
		MaterialPtr MPillar = make_shared<Material>();
		MPillar->BaseColour.TextureV3 = TPillar;
		Pillar->SetMaterialBySlot(0, MPillar);

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


	Wall->Transform.Rotation.z += 50.0f * GetFDeltaTime();


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
	
	Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

	if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {

		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime());
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime());
		GameInput->CursorToggle(true);
	}
	else {
		GameInput->CursorToggle(false);
	}
	if (GameInput->IsMouseButtonDown(MouseButtons::LEFT)) {
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
