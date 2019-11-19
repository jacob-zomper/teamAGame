#ifndef StartScreen_H
#define StartScreen_H

#include <SDL.h>
#include "Player.h"

class StartScreen
{
public:
    StartScreen(SDL_Texture *start, SDL_Texture *btn);
    static const int START_BUTTON_WIDTH = 250;
    static const int START_BUTTON_HEIGHT = 80;
    static const int START_BUTTON_X = 1280 - 400;
    static const int START_BUTTON_Y = 720 - 150;
    
    bool notStarted = true;

    SDL_Texture* gBackground;
    SDL_Texture* btn_start;

    void handleEvent(SDL_Event &e);
    void render(SDL_Renderer *gRenderer);
};

#endif