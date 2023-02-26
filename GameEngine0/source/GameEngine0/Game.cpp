#include "GameEngine0\Game.h"
#include "GameEngine0/Graphics/GraphicsEngine.h"
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
}

Game::~Game()
{
	Graphics = nullptr;
	cout << "Game Over" << endl;
}

void Game::Run()
{
	if (!bIsGameOver) {
		Graphics->CreateShader({
			L"Game/Shaders/SimpleShader/SimpleShader.svert",
			L"Game/Shaders/SimpleShader/SimpleShader.sfrag"
			});
		Graphics->CreateVAO(GeometricShapes::Triangle);
		Graphics->CreateVAO(GeometricShapes::Polygon);
		Graphics->CreateVAO(GeometricShapes::Circle);
		Graphics->CreateVAO(GeometricShapes::Free);
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
	SDL_Event PollEvent;
	while(SDL_PollEvent(&PollEvent)) {
		switch (PollEvent.type) {
		case SDL_QUIT : 
			bIsGameOver = true;
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{

}

void Game::Draw()
{
	Graphics->Draw();
}

void Game::CloseGame()
{

}
