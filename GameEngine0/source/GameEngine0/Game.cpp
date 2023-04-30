#include "GameEngine0\Game.h"
#include "GameEngine0/Graphics/GraphicsEngine.h"
#include "GameEngine0/Graphics/Model.h"
#include "GameEngine0/Input.h"
#include "GameEngine0/Graphics/Camera.h"
#include "GameEngine0/Graphics/Material.h"
#include "GameEngine0/Collisions/Collision.h"

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

void Game::RemoveModelFromGame(ModelPtr& ModelToRemove)
{
	Graphics->RemoveModel(ModelToRemove);
	ModelToRemove = nullptr;
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

		CollectStar = Graphics->ImportModel("Game/Models/lost-wish-collectable/Star/starbit_low.fbx", TextureShader);
		CollectScroll = Graphics->ImportModel("Game/Models/fantasy-scroll/Scroll/Collectable OBJ.obj", TextureShader);
		CollectAnk = Graphics->ImportModel("Game/Models/ankh-asset/Ank/ankh2.fbx", TextureShader);

		CollectStar->SetMaterialBySlot(0, MGrey);
		CollectScroll->SetMaterialBySlot(0, MGrid);

		CollectScroll->AddCollisionToModel(Vector3(2.0f));

		CollectStar->Transform.Location = Vector3(-20.0f, 0.0f, -20.0f);
		CollectStar->Transform.Scale = Vector3(0.007f);
		CollectScroll->Transform.Location = Vector3(0.0f, 0.0f, -2.0f);
		CollectScroll->Transform.Scale = Vector3(0.07f);

		CollectAnk->Transform.Location = Vector3(20.0f, -2.0f, 20.0f);
		CollectAnk->Transform.Scale = Vector3(0.007f);

		CollectAnk->AddCollisionToModel(Vector3(2.0f));
		CollectStar->AddCollisionToModel(Vector3(2.0f));

		Portal = Graphics->ImportModel("Game/Models/portal/Portal/portal.fbx", TextureShader);
		Portal->Transform.Scale = Vector3(0.005f);
		Portal->Transform.Rotation.y = 90.0f;
		Portal->Transform.Location = Vector3(2.0f, -2.0f, 0.0f);

		AHouse = Graphics->ImportModel("Game/Models/abandoned-house/House/abandonhouse.fbx", TextureShader);
		AHouse->Transform.Scale = Vector3(1.5f);
		AHouse->Transform.Rotation.x = -90.0f;
		AHouse->Transform.Location = Vector3(20.0f, -2.0f, 20.0f);

		Shrine = Graphics->ImportModel("Game/Models/japanese-shrine/Shrine/Shrine_02.fbx", TextureShader);
		Shrine->Transform.Scale = Vector3(0.05f);
		//Shrine->Transform.Rotation.x = 90.0f;
		Shrine->Transform.Location = Vector3(-20.0f, -2.0f, -20.0f);

		Floor = Graphics->ImportModel("Game/Models/DamageWall/SM_Wall_Damaged_2x1_A.obj", TextureShader);
		Floor->Transform.Scale = Vector3(1.0f, 1.0f, 0.03f);
		Floor->Transform.Rotation.x = 90.0f;
		Floor->Transform.Location = Vector3(0.0f, -2.75f, -15.0f);

		Portal->AddCollisionToModel(Vector3(1.25f, 4.0f, 10.0f), Vector3(0.0f, 2.0f, 0.0f));

		TexturePtr TPortal = Graphics->CreateTexture("Game/Models/portal/textures/portalNormal.png");
		MaterialPtr MPortal = make_shared<Material>();
		MPortal->BaseColour.TextureV3 = TPortal;
		Portal->SetMaterialBySlot(0, MPortal);

		TexturePtr TShrine = Graphics->CreateTexture("Game/Models/japanese-shrine/textures/Shrine_02_Main_01_SH2_BB_Base_02_NormalOpe.png");
		MaterialPtr MShrine = make_shared<Material>();
		MShrine->BaseColour.TextureV3 = TShrine;
		Shrine->SetMaterialBySlot(0, MShrine);

		TexturePtr THouse = Graphics->CreateTexture("Game/Models/abandoned-house/textures/AbHouse_Base_Color.png");
		MaterialPtr MHouse = make_shared<Material>();
		MHouse->BaseColour.TextureV3 = THouse;
		AHouse->SetMaterialBySlot(0, MHouse);

		TexturePtr TFloor = Graphics->CreateTexture("Game/Models/Textures/GreySquare.jpg");
		MaterialPtr MFloor = make_shared<Material>();
		MFloor->BaseColour.TextureV3 = TFloor;
		Floor->SetMaterialBySlot(1, MFloor);

		TexturePtr TAnk = Graphics->CreateTexture("Game/Models/ankh-asset/Ank/ankh2_BaseColor.png");
		MaterialPtr MAnk = make_shared<Material>();
		MAnk->BaseColour.TextureV3 = TAnk;
		CollectAnk->SetMaterialBySlot(0, MAnk);

		TexturePtr TStar = Graphics->CreateTexture("Game/Models/lost-wish-collectable/Star/textures/m_Starbit_Normal_DirectX.png");
		MaterialPtr MStar = make_shared<Material>();
		MStar->BaseColour.TextureV3 = TStar;
		CollectStar->SetMaterialBySlot(0, MStar);

		TexturePtr TScroll = Graphics->CreateTexture("Game/Models/fantasy-scroll/Scroll/Collectable_lambert1_BaseColor.png");
		MaterialPtr MScroll = make_shared<Material>();
		MScroll->BaseColour.TextureV3 = TScroll;
		CollectScroll->SetMaterialBySlot(1, MScroll);

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

		Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta);
		Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta);
		GameInput->CursorToggle(true);
	}
	else {
		GameInput->CursorToggle(false);
	}
	if (GameInput->IsMouseButtonDown(MouseButtons::LEFT)) {
		Graphics->EngineDefaultCam->ZoomFOV(10.0f);
	}

}

void Game::Update()
{
	static double LastFrameTime = 0.0;
	double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
	double NewDeltaTime = CurrentFrameTime - LastFrameTime;
	DeltaTime = NewDeltaTime / 1000.0;
	LastFrameTime = CurrentFrameTime;


	//CollectAnk->Transform.Rotation.z += 50.0f * GetFDeltaTime();
	//Poly1->Transform.Location.x += 0.1 * GetFDeltaTime();



	Graphics->EngineDefaultCam->Update();

	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();
	if (CollectAnk != nullptr && CamCol->IsOverLapping(*CollectAnk->GetCollision()))
	{
		RemoveModelFromGame(CollectAnk);
	}

	if (CollectScroll != nullptr && CamCol->IsOverLapping(*CollectScroll->GetCollision()))
	{
		RemoveModelFromGame(CollectScroll);
	}

	if (CollectStar != nullptr && CamCol->IsOverLapping(*CollectStar->GetCollision()))
	{
		RemoveModelFromGame(CollectStar);
	}
}

void Game::Draw()
{
	Graphics->ClearGraphics();

	Graphics->Draw();

	CollisionPtr CamCol = Graphics->EngineDefaultCam->GetCameraCollision();

	if (CollectAnk != nullptr && CamCol->IsOverLapping(*CollectAnk->GetCollision()))
	{
		CamCol->DebugDraw(Vector3(255.0f, 0.0f, 0.0f));
	}
	else
	{
		CamCol->DebugDraw(Vector3(255.0f));
	}

	Graphics->PresentGraphics();
}

void Game::CloseGame()
{
	delete GameInput;
}
