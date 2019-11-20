#ifndef DifficultySelectionScreen_H
#define DifficultySelectionScreen_H

#include <SDL.h>
#include "Player.h"

class DifficultySelectionScreen
{
public:
    DifficultySelectionScreen(SDL_Texture *diff, SDL_Texture *ebtn, SDL_Texture *mbtn, SDL_Texture *hbtn);
    int EASY_BUTTON_WIDTH = 250;
    int EASY_BUTTON_HEIGHT = 80;
    int EASY_BUTTON_X = 515;
    int EASY_BUTTON_Y = 360;

    int MEDIUM_BUTTON_WIDTH = 250;
    int MEDIUM_BUTTON_HEIGHT = 80;
    int MEDIUM_BUTTON_X = 515;
    int MEDIUM_BUTTON_Y = 475;

    int HARD_BUTTON_WIDTH = 250;
    int HARD_BUTTON_HEIGHT = 80;
    int HARD_BUTTON_X = 515;
    int HARD_BUTTON_Y = 590;

    int selectedDiff; //selected diffuculty, 1 for easy, 2 for med, 3 for hard, 0 default

    SDL_Texture* gBackground;
    SDL_Texture* btn_easy;
    SDL_Texture* btn_med;
    SDL_Texture* btn_hard;

    int handleEvent(SDL_Event &e);
    void render(SDL_Renderer *gRenderer);
};

#endif