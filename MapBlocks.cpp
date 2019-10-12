#include <SDL.h>
#include "Player.h"
#include "MapBlocks.h"
#include "iostream"
#include <vector>

SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
    if(gRenderer == nullptr){
        return nullptr;
    }
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

WallBlock::WallBlock(){};

Stalagmite::Stalagmite()
{
    SDL_Renderer *gRenderer= nullptr;
    Stalagmite(1,1,gRenderer);
}
Stalagmite::Stalagmite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer)
{
    STALAG_ABS_X = rand() % LEVEL_WIDTH;
    STALAG_ABS_Y = LEVEL_HEIGHT;//growing from bottom of cave
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    // These should be the same first
    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;

    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;

    stalagShapeNum = rand() % 4 + 1;
    if (stalagShapeNum == 1) {
        sprite = loadImage("sprites/stalagm1.png", gRenderer);
    }
    else if (stalagShapeNum == 2) {
        sprite = loadImage("sprites/stalagm2.png", gRenderer);
    }
    else if (stalagShapeNum == 3) {
        sprite = loadImage("sprites/stalagm3.png", gRenderer);
    }
    else if (stalagShapeNum == 4) {
        sprite = loadImage("sprites/stalagm4.png", gRenderer);
    }
}

Stalagtite::Stalagtite()
{
    SDL_Renderer *gRenderer= nullptr;
    Stalagtite(1,1,gRenderer);
}
Stalagtite::Stalagtite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer)
{
    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;

    STALAG_ABS_X = rand() % LEVEL_WIDTH;
    STALAG_ABS_Y = WallBlock::block_side;//growing from top of cave
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    // These should be the same first
    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;

    stalagShapeNum = rand() % 4 + 1;
    if (stalagShapeNum == 1) {
        sprite = loadImage("sprites/stalagt1.png", gRenderer);
    }
    else if (stalagShapeNum == 2) {
        sprite = loadImage("sprites/stalagt2.png", gRenderer);
    }
    else if (stalagShapeNum == 3) {
        sprite = loadImage("sprites/stalagt3.png", gRenderer);
    }
    else if (stalagShapeNum == 4) {
        sprite = loadImage("sprites/stalagt4.png", gRenderer);
    }
}

FlyingBlock::FlyingBlock()
{
    SDL_Renderer *gRenderer= nullptr;
    FlyingBlock(1, 1, gRenderer);
}

FlyingBlock::FlyingBlock(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer)
{
    BLOCK_ABS_X = rand() % LEVEL_WIDTH;
    BLOCK_ABS_Y = rand() % LEVEL_HEIGHT;

    // These should be the same first
    BLOCK_REL_X = BLOCK_ABS_X;
    BLOCK_REL_Y = BLOCK_ABS_Y;

    // BLOCK_WIDTH = 25 + (rand() % 100);
    // BLOCK_HEIGHT = 25 + (rand() % 100);
    //Standard Enemy plane size
    BLOCK_WIDTH = 125; 
    BLOCK_HEIGHT = 53;

    sprite1 = loadImage("sprites/EnemyPlaneK1.png", gRenderer);
    sprite2 = loadImage("sprites/EnemyPlaneK2.png", gRenderer);
    
    FB_sprite = { BLOCK_ABS_X,  BLOCK_ABS_Y, BLOCK_WIDTH, BLOCK_HEIGHT};
    FB_hitbox = FB_sprite;
}

MapBlocks::MapBlocks()
{
    SDL_Renderer *gRenderer= nullptr;
    MapBlocks(1, 1, gRenderer = nullptr);
}

MapBlocks::MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer)
{

    blocks_arr = new FlyingBlock[BLOCKS_N];
    stalagm_arr = new Stalagmite[STALAG_N];
    stalagt_arr = new Stalagtite[STALAG_N];

    int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        blocks_arr[i] = FlyingBlock(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer); // Initiating each FlyingBlock
    }
    for (i=0; i < STALAG_N; i++)
    {
        stalagm_arr[i] = Stalagmite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer);//Initiate the stalagmites
    }
    for (i=0; i < STALAG_N; i++)
    {
        stalagt_arr[i] = Stalagtite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer);//Initiate the stalagtites
    }
}

bool MapBlocks::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

void MapBlocks::moveBlocks(int camX, int camY)
{
    int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        blocks_arr[i].BLOCK_REL_X = blocks_arr[i].BLOCK_ABS_X - camX;
        blocks_arr[i].BLOCK_REL_Y = blocks_arr[i].BLOCK_ABS_Y - camY;
	}
    for (i = 0; i < STALAG_N; i++)
    {
        stalagm_arr[i].STALAG_REL_X = stalagm_arr[i].STALAG_ABS_X - camX;
        stalagm_arr[i].STALAG_REL_Y = stalagm_arr[i].STALAG_ABS_Y-camY - WallBlock::block_side - stalagm_arr[i].STALAG_HEIGHT;
    }
    for (i = 0; i < STALAG_N; i++)
    {
        stalagt_arr[i].STALAG_REL_X = stalagt_arr[i].STALAG_ABS_X - camX;
        // stalagt_arr[i].STALAG_REL_Y = stalagt_arr[i].STALAG_ABS_Y-camY - WallBlock::block_side - stalagt_arr[i].STALAG_HEIGHT;
    }
}

void MapBlocks::checkCollision(Player *p)
{
	int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        // If there's a collision, cancel the player's move
		if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
            p->undoXMove();
            p->undoYMove();
			// If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
            {
                p->setPosX(std::max(blocks_arr[i].BLOCK_REL_X - p->PLAYER_WIDTH, 0));
                p->redoYMove();
            }
        }
    }
    for (i = 0; i < STALAG_N; i++)
    {
        // If there's a collision, cancel the player's move
        if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            p->undoXMove();
            p->undoYMove();
            // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
            {
                p->setPosX(std::max(stalagm_arr[i].STALAG_REL_X - p->PLAYER_WIDTH, 0));
                p->redoYMove();
            }
        }
        //now check for stalagtites
        if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            p->undoXMove();
            p->undoYMove();
            // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
            {
                p->setPosX(std::max(stalagt_arr[i].STALAG_REL_X - p->PLAYER_WIDTH, 0));
                p->redoYMove();
            }
        }
    }
    if(p->getPosY()>=720-72-p->PLAYER_HEIGHT){//floor collisions stopped working, not sure why, this needs a better fix but this works
        p->setPosY(720-72-p->PLAYER_HEIGHT);
        p->undoYMove();
    }
}

void MapBlocks::checkCollision(Enemy *e)
{
	int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        // If there's a collision, cancel the enemy's move
		if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
            e->undoXMove();
            e->undoYMove();
			// If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
            {
                e->setPosX(std::max(blocks_arr[i].BLOCK_REL_X - e->getWidth(), 0));
                e->redoYMove();
            }
        }
    }
    for (i = 0; i < STALAG_N; i++)
    {
        // If there's a collision, cancel the player's move
        if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            e->undoXMove();
            e->undoYMove();
            // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
            {
                e->setPosX(std::max(stalagm_arr[i].STALAG_REL_X - e->getWidth(), 0));
                e->redoYMove();
            }
        }

        if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            e->undoXMove();
            e->undoYMove();
            // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
            if (checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
            {
                e->setPosX(std::max(stalagt_arr[i].STALAG_REL_X - e->getWidth(), 0));
                e->redoYMove();
            }
        }
    }
}


void MapBlocks::render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
{
    int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        // Only render the FlyingBlock if will be screen
        if (blocks_arr[i].BLOCK_REL_X < SCREEN_WIDTH && blocks_arr[i].BLOCK_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT};
            if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
                 SDL_RenderCopyEx(gRenderer, blocks_arr[i].sprite1, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
            }
            else {
                SDL_RenderCopyEx(gRenderer, blocks_arr[i].sprite2, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
            }
            blocks_arr[i].FB_hitbox=blocks_arr[i].FB_sprite;
        }
    }

    // Render walls
    for(i = 0; i < SCREEN_WIDTH; i+= WallBlock::block_side)
    {
        SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
        SDL_Rect fillRectWall1 = { i, SCREEN_HEIGHT - WallBlock::block_side, WallBlock::block_side, WallBlock::block_side };
        SDL_RenderFillRect(gRenderer, &fillRectWall1);

        SDL_Rect fillRectWall2 = {i, 0, WallBlock::block_side, WallBlock::block_side};
        SDL_RenderFillRect(gRenderer, &fillRectWall2);
    }

    for (i = 0; i < STALAG_N; i++)
    {
        // Only render the Stalag if will be screen
        if (stalagm_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagm_arr[i].STALAG_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT};
            SDL_RenderCopyEx(gRenderer, stalagm_arr[i].sprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < STALAG_N; i++)
    {
        // Only render the Stalag if will be screen
        // if (stalagt_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagt_arr[i].STALAG_REL_Y < SCREEN_HEIGHT)
        // {
            SDL_Rect fillRect = {stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT};
            SDL_RenderCopyEx(gRenderer, stalagt_arr[i].sprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        // }
    }

}

