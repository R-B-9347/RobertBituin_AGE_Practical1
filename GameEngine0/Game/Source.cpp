#include "GameEngine0/Game.h"

int main(int argc, char** argv) {
	Game::GetGameInstance().Start("GameEngine0 | Omegalul", false, 1200, 1200);

	Game::GetGameInstance();

	Game::DestroyGameInstance();

	return 0;

}