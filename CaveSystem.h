#ifndef CaveSystem_H
#define CaveSystem_H

#include <SDL.h>
#include <string>
#include <iostream>
#include "Player.h"

class CaveBlock
{
public:
    // absolute coordinates of each CaveBlock
    int CAVE_BLOCK_ABS_X;
    int CAVE_BLOCK_ABS_Y;

    // coordinates of each CaveBlock relative to camera
    int CAVE_BLOCK_REL_X;
    int CAVE_BLOCK_REL_Y;

    int enabled; // Is the cave block going to be visible? 1 = yes, 0 = no

    static const int CAVE_BLOCK_HEIGHT = 20;
    static const int CAVE_BLOCK_WIDTH = 20;
    CaveBlock();
    std::string toString();
};

class CaveSystem
{
public:
    static const int CAVE_SYSTEM_HEIGHT = 720 / CaveBlock::CAVE_BLOCK_HEIGHT;
    static const int CAVE_SYSTEM_WIDTH = 2000 / CaveBlock::CAVE_BLOCK_WIDTH;
    bool isEnabled = false;
    CaveBlock *cave_system[CAVE_SYSTEM_HEIGHT][CAVE_SYSTEM_WIDTH];

    CaveSystem();
    CaveSystem(int camX, int camY, int SCREEN_WIDTH);

    void render(SDL_Renderer *gRenderer);
    void moveCaveBlocks(int camX, int camY);
    void checkCollision(Player *p);
    void render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer);
};

#endif
