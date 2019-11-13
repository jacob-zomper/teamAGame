#include "StartScreen.h"
#include <SDL.h>
#include <SDL_image.h>


StartScreen::StartScreen(SDL_Texture *start, SDL_Texture *btn){
	gBackground=start;
	btn_start=btn;
}

void StartScreen::handleEvent(SDL_Event&e)
{
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inStart = true;

		if(x < START_BUTTON_X){ inStart = false;}
		else if(x > START_BUTTON_X + START_BUTTON_WIDTH){ inStart = false;}
		else if(y < START_BUTTON_Y){ inStart = false;}
		else if(y > START_BUTTON_Y + START_BUTTON_HEIGHT){ inStart = false;}

		if(inStart && e.type == SDL_MOUSEBUTTONUP){
			notStarted=false;
		}
	}
}

void StartScreen::render(SDL_Renderer *gRenderer)
{
	SDL_Rect bgRect = {0,0, 1280, 720};
	SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

	SDL_Rect fillRectButton = {START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_start, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);
}

