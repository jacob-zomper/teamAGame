#ifndef MapBlocks_H
#define MapBlocks_H

#include <SDL.h>
#include "Player.h"
#include "Enemy.h"

class WallBlock
{
public:
    static const int block_side = 72;
    WallBlock();
};

class FlyingBlock
{
public:
    // absolute coordinates of each FlyingBlock
    int BLOCK_ABS_X;
    int BLOCK_ABS_Y;

    // coordinates of each FlyingBlock relative to camera
    int BLOCK_REL_X;
    int BLOCK_REL_Y;

    int BLOCK_HEIGHT;
    int BLOCK_WIDTH;

    int BLOCK_SPRITE; // Map to which sprite image this FlyingBlock will use.

    FlyingBlock();
    FlyingBlock(int LEVEL_WIDTH, int LEVEL_HEIGHT);
};

class MapBlocks
{

public:
    static const int BLOCKS_STARTING_N = 500;
    int BLOCKS_N = 500;
    static const int BLOCK_HEIGHT = 100;
    static const int BLOCK_WIDTH = 100;
    FlyingBlock *blocks_arr;

    MapBlocks();
    MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT);
    bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight);

    void moveBlocks(int camX, int camY);
	void checkCollision(Player *p);
	void checkCollision(Enemy *e);
    void render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer);
};

#endif