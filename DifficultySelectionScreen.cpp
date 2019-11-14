#include "DifficultySelectionScreen.h"
#include <SDL.h>
#include <SDL_image.h>

DifficultySelectionScreen::DifficultySelectionScreen(SDL_Texture *diff, SDL_Texture *ebtn, SDL_Texture *mbtn, SDL_Texture *hbtn){
	gBackground=diff;
	btn_easy=ebtn;
    btn_med=mbtn;
    btn_hard=hbtn;
}

int DifficultySelectionScreen::handleEvent(SDL_Event&e)
{
	if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		selectedDiff = 1;
		if (x < EASY_BUTTON_X){ selectedDiff = 0; }
        else if (x > EASY_BUTTON_X + EASY_BUTTON_WIDTH){ selectedDiff = 0; }
        else if (y < EASY_BUTTON_Y){ selectedDiff = 0; }
        else if (y > EASY_BUTTON_Y + EASY_BUTTON_HEIGHT){selectedDiff = 0; }

        if (selectedDiff == 1 && e.type == SDL_MOUSEBUTTONUP){
            return selectedDiff;
        }

        selectedDiff = 2;
        if (x < MEDIUM_BUTTON_X){ selectedDiff = 0; }
        else if (x > MEDIUM_BUTTON_X + MEDIUM_BUTTON_WIDTH){ selectedDiff = 0; }
        else if (y < MEDIUM_BUTTON_Y){ selectedDiff = 0; }
        else if (y > MEDIUM_BUTTON_Y + MEDIUM_BUTTON_HEIGHT){ selectedDiff = 0; }

        if (selectedDiff == 2 && e.type == SDL_MOUSEBUTTONUP){
            return selectedDiff;
        }
        
        selectedDiff = 3;
        if (x < HARD_BUTTON_X){ selectedDiff = 0; }
        else if (x > HARD_BUTTON_X + HARD_BUTTON_WIDTH){ selectedDiff = 0; }
        else if (y < HARD_BUTTON_Y){ selectedDiff = 0; }
        else if (y > HARD_BUTTON_Y + HARD_BUTTON_HEIGHT){ selectedDiff = 0; }

        if (selectedDiff == 3 && e.type == SDL_MOUSEBUTTONUP){
            return selectedDiff;
        }
	}
    return 0;
}

void DifficultySelectionScreen::render(SDL_Renderer *gRenderer)
{
	SDL_Rect bgRect = {0,0, 1280, 720};
	SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);

	SDL_Rect fillRectButton = {EASY_BUTTON_X, EASY_BUTTON_Y, EASY_BUTTON_WIDTH, EASY_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_easy, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);

    fillRectButton = {MEDIUM_BUTTON_X, MEDIUM_BUTTON_Y, MEDIUM_BUTTON_WIDTH, MEDIUM_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_med, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);

    fillRectButton = {HARD_BUTTON_X, HARD_BUTTON_Y, HARD_BUTTON_WIDTH, HARD_BUTTON_HEIGHT};
	SDL_RenderCopyEx(gRenderer, btn_hard, nullptr, &fillRectButton, 0.0, nullptr, SDL_FLIP_NONE);
}
