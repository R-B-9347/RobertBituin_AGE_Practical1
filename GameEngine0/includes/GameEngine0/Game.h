#pragma once
#include "CoreMinimal.h"

class Input;

class Game {
public:
	//Get game instance or create one
	static Game& GetGameInstance();

	//Destroy Game running destructor
	static void DestroyGameInstance();

	//Game Start
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	double GetDeltaTime() { return DeltaTime; }

	float GetFDeltaTime() { return static_cast <float>(DeltaTime); }

	GEptr GetGraphicsEngine() { return Graphics; }

	void CloseApp() { bIsGameOver = true; }
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

	TexturePtr DefaultTexture;

	double DeltaTime;

	Input* GameInput;

	MeshPtr Tri;
	MeshPtr Poly;
};