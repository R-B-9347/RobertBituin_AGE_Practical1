#pragma once
#include "SDL2/SDL.h"

enum MouseButtons {
	LEFT = SDL_BUTTON_LEFT,
	MIDDLE = SDL_BUTTON_MIDDLE,
	RIGHT = SDL_BUTTON_RIGHT
};

class Input {
public:
	Input();

	void ProcessInput();

	bool IsKeyDown(SDL_Scancode key);

	bool IsMouseButtonDown(MouseButtons Button);

private:
	void SetMouseButtonStatez(Uint8 ButtonIndex, bool CurrentState);
	void OnMouseMove(SDL_MouseMotionEvent& MEvent);
	void OnMouseScroll(SDL_MouseWheelEvent& MEvent);

public:
	int MouseX, MouseY;

	int MouseXDelta, MouseYDelta;

	float ScrollDelta;
private:
	const Uint8* KeyboardState;

	bool MouseButtonStates[10] = { false };

};