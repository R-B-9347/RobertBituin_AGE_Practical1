#include "..\..\includes\GameEngine0\Input.h"
#include "GameEngine0/Game.h"
#include "SDL2/SDL.h"
#include <iostream>

using namespace std;
Input::Input()
{
	KeyboardState = SDL_GetKeyboardState(NULL);
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;
	MouseX = MouseY = 0;
}

void Input::ProcessInput()
{
	MouseXDelta = MouseYDelta = 0;
	ScrollDelta = 0;
	SDL_Event PollEvent;
	while (SDL_PollEvent(&PollEvent)) {
		switch (PollEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			SetMouseButtonStatez(PollEvent.button.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			SetMouseButtonStatez(PollEvent.button.button, false);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMove(PollEvent.motion);
			break;
		case SDL_MOUSEWHEEL:
			OnMouseScroll(PollEvent.wheel);
			break;

		case SDL_KEYDOWN :
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT:
			 Game::GetGameInstance().CloseApp();
			break;
		default:
			break;
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	if (KeyboardState == nullptr) {
		cout << "No keybvoard state Detected!" << endl;
		return false;
	}
	return static_cast<bool>(KeyboardState[key]);
}

bool Input::IsMouseButtonDown(MouseButtons Button)
{
	return MouseButtonStates[Button];
}

void Input::CursorToggle(bool bVisibility)
{
	static SDL_bool bIsVisible = SDL_FALSE;

	if (bVisibility && bIsVisible == SDL_FALSE) {
		bIsVisible = SDL_TRUE;
		SDL_SetRelativeMouseMode(bIsVisible);
	}

	else if (!bVisibility && bIsVisible == SDL_TRUE) {
		bIsVisible = SDL_FALSE;
		SDL_SetRelativeMouseMode(bIsVisible);
	}
}

void Input::SetMouseButtonStatez(Uint8 ButtonIndex, bool CurrentState)
{
	MouseButtonStates[ButtonIndex] = CurrentState;
}

void Input::OnMouseMove(SDL_MouseMotionEvent& MEvent)
{
	MouseX = MEvent.x;
	MouseY = MEvent.y;

	MouseXDelta += MEvent.xrel;
	MouseYDelta += MEvent.yrel;
}

void Input::OnMouseScroll(SDL_MouseWheelEvent& MEvent)
{
	ScrollDelta += MEvent.preciseY;

}
