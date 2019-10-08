#include "GameOver.h"
#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"

GameOver::GameOver(){};

void GameOver::stopGame(Player *player, MapBlocks *map_blocks)
{
    player->setVelX(0);
    player->setVelY(0);
    map_blocks->BLOCKS_N = 0;
}

void GameOver::handleEvent(SDL_Event &e, Player *player, MapBlocks *map_blocks)
{

    //If mouse event happened
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < RESTART_BUTTON_X)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > RESTART_BUTTON_X + RESTART_BUTTON_WIDTH)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < RESTART_BUTTON_Y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > RESTART_BUTTON_Y + RESTART_BUTTON_HEIGHT)
        {
            inside = false;
        }

        //Mouse is inside button
        if(inside){ restart(player, map_blocks); }
    }
}

void GameOver::render(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xa1);
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_Rect fillRectOverlay = {0, 0, 1280, 720};
    SDL_RenderFillRect(gRenderer, &fillRectOverlay);

    SDL_SetRenderDrawColor(gRenderer, 0x4F, 0xa7, 0x00, 0xFF);
    SDL_Rect fillRectButton = {RESTART_BUTTON_X, RESTART_BUTTON_Y, RESTART_BUTTON_WIDTH, RESTART_BUTTON_HEIGHT};
    SDL_RenderFillRect(gRenderer, &fillRectButton);

}

void GameOver::restart(Player *player, MapBlocks *map_blocks)
{
    map_blocks->BLOCKS_N = 1000;
    map_blocks = new MapBlocks(LEVEL_WIDTH, LEVEL_HEIGHT);
    isGameOver = false;
}