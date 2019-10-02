#ifndef MapBlocks_H
#define MapBlocks_H

#include <SDL.h>
#include "Player.h"

class Block
{
public:
    // absolute coordinates of each block
    int BLOCK_ABS_X;
    int BLOCK_ABS_Y;

    // coordinates of each block relative to camera
    int BLOCK_REL_X;
    int BLOCK_REL_Y;

    int BLOCK_SPRITE; // Map to which sprite image this block will use.

    Block();
    Block(int LEVEL_WIDTH, int LEVEL_HEIGHT);
};

class MapBlocks
{

public:
    static const int BLOCKS_N = 1000;
    static const int BLOCK_HEIGHT = 100;
    static const int BLOCK_WIDTH = 100;
    Block *blocks_arr;

    MapBlocks();
    MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT);
    bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight);

    void moveBlocksAndCheckCollision(Player *p, int camX, int camY);
    void render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer);
};

#endif