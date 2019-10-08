#ifndef GameOver_H
#define GameOver_H

#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"

class GameOver
{
public:
    bool isGameOver = false;
    static const int RESTART_BUTTON_WIDTH = 200;
    static const int RESTART_BUTTON_HEIGHT = 50;
    static const int RESTART_BUTTON_X = (int)(1280/2) - 100;
    static const int RESTART_BUTTON_Y = (int)(720/1.5) - 25;
    GameOver();

    void stopGame(Player*, MapBlocks*);
    void handleEvent(SDL_Event &e, Player *player, MapBlocks *map_blocks);
    void render(SDL_Renderer *gRenderer);
private:
    void restart(Player *player, MapBlocks *map_blocks);
    int LEVEL_WIDTH = 100000;
    int LEVEL_HEIGHT = 2000;
};

#endif