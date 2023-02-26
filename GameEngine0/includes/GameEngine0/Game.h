#pragma once
#include "CoreMinimal.h"


class Game {
public:
	//Get game instance or create one
	static Game& GetGameInstance();

	//Destroy Game running destructor
	static void DestroyGameInstance();

	//Game Start
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);
private:
	Game();
	~Game();

	//game loop
	void Run();

	//Handle input
	void ProcessInpout();

	//game logic
	void Update();

	//Graphics
	void Draw();

	void CloseGame();

private:
	//end game
	bool bIsGameOver;

	GEptr Graphics;
};