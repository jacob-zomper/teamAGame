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
WallBlock::WallBlock(int num, bool cave){
    CEILING_ABS_X = num * block_side;
    CEILING_ABS_Y = 0;
    CEILING_REL_X = CEILING_ABS_X;
    CEILING_REL_Y = CEILING_ABS_Y; 
    if(cave){
        enabled=true;
    }else{
        enabled=false;
    }
}

Stalagmite::Stalagmite()
{
    SDL_Renderer *gRenderer= nullptr;
    Stalagmite(1,1,gRenderer, 5500, 2000, 0, 0);
}
Stalagmite::Stalagmite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    STALAG_ABS_X = rand() % LEVEL_WIDTH;
    STALAG_ABS_Y = LEVEL_HEIGHT;//growing from bottom of cave
	while ((STALAG_ABS_X - 1280) % cave_freq <= cave_width) {
		STALAG_ABS_X = rand() % LEVEL_WIDTH;
	}
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    // These should be the same first
    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;

    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;

    //if  in open air enabled = false
    if(STALAG_ABS_X>(openAir*72) && STALAG_ABS_X+STALAG_WIDTH<(openAir+openAirLength)*72){
        enabled=false;
    }else{
        enabled=true;
    }

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
    Stalagtite(1,1,gRenderer, 5500, 2000, 0, 0);
}
Stalagtite::Stalagtite(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    STALAG_WIDTH = rand() % 16 + 60;
    STALAG_HEIGHT = rand() % 141 + 50;

    STALAG_ABS_X = rand() % LEVEL_WIDTH;

    STALAG_ABS_Y = WallBlock::block_side;//growing from top of cave
	while ((STALAG_ABS_X - 1280) % cave_freq <= cave_width) {
		STALAG_ABS_X = rand() % LEVEL_WIDTH;
	}
    //STALAG_ABS_Y= rand() % LEVEL_HEIGHT;

    // These should be the same first
    STALAG_REL_X = STALAG_ABS_X;
    STALAG_REL_Y = STALAG_ABS_Y;

    //if open air enabled = false
    if(STALAG_ABS_X>(openAir*72) && STALAG_ABS_X+STALAG_WIDTH<(openAir+openAirLength)*72){
        enabled=false;
    }else{
        enabled=true;
    }

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

    beenShot = 0;
    acceleration = 0;
}

Turret::Turret()
{
    SDL_Renderer *gRenderer= nullptr;
    Turret(1, 1, gRenderer, 5500, 2000, 0, 0);
}

Turret::Turret(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width, int openAir, int openAirLength)
{
    BLOCK_ABS_X = rand() % LEVEL_WIDTH;
	BLOCK_ABS_Y = LEVEL_HEIGHT - WallBlock::block_side - Turret::BLOCK_HEIGHT;
	if (rand() % 2 == 1) {
		BLOCK_ABS_Y = LEVEL_HEIGHT - 720 + WallBlock::block_side;
	}
	while ((BLOCK_ABS_X - 1280) % cave_freq <= cave_width) {
		BLOCK_ABS_X = rand() % LEVEL_WIDTH;
	}

    // These should be the same first
    BLOCK_REL_X = BLOCK_ABS_X;
    BLOCK_REL_Y = BLOCK_ABS_Y;

    // BLOCK_WIDTH = 25 + (rand() % 100);
    // BLOCK_HEIGHT = 25 + (rand() % 100);
    //Standard Enemy plane size
    BLOCK_WIDTH = 50;
    BLOCK_HEIGHT = 50;

    //if open air enabled = false
    if(BLOCK_ABS_X>(openAir*72) && BLOCK_ABS_X+BLOCK_WIDTH<(openAir+openAirLength)*72 && BLOCK_ABS_Y==LEVEL_HEIGHT -720 + WallBlock::block_side){
        enabled=false;
    }else{
        enabled=true;
        if(BLOCK_REL_Y < 360){
            sprite = loadImage("sprites/topturret.png", gRenderer);
        }
        else{
            sprite = loadImage("sprites/bottomturret.png", gRenderer);
        }
    }

    FB_sprite = { BLOCK_ABS_X,  BLOCK_ABS_Y, BLOCK_WIDTH, BLOCK_HEIGHT};
    FB_hitbox = FB_sprite;

	last_move = SDL_GetTicks();
}

int Turret::getRelX() { return BLOCK_REL_X; }
int Turret::getRelY() { return BLOCK_REL_Y; }
int Turret::getAbsX() { return BLOCK_ABS_X; }
int Turret::getAbsY() { return BLOCK_ABS_Y; }

Bullet * Turret::handleFiring(int posX, int posY) {
	time_since_move = SDL_GetTicks() - last_move;
	Bullet * b = nullptr;
	if (time_since_move >= SHOOT_FREQ) {
		last_move = SDL_GetTicks();
		int xDist = posX - BLOCK_REL_X;
		int yDist = posY - BLOCK_REL_Y;
		double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
		double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
		if (BLOCK_REL_Y >= posY){
			b = new Bullet(BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y - 20, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400);
		}
		else {
			b = new Bullet(BLOCK_REL_X + BLOCK_WIDTH / 2, BLOCK_REL_Y + 5 + BLOCK_HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400);
		}
	}
	return b;
}

Explosion::Explosion()
{
    SDL_Renderer *gRenderer= nullptr;
    Explosion(1, 1, gRenderer);
}

Explosion::Explosion(int x_loc, int y_loc, SDL_Renderer *gRenderer)
{
	// Initialize all necessary variables
	current_size = (double) INITIAL_EXPLOSION_SIZE;
	center_x = x_loc;
	center_y = y_loc;
	abs_x = center_x - current_size / 2;
	abs_y = center_y - current_size / 2;
    sprite = loadImage("sprites/Explosion.png", gRenderer);
	explosion_time = SDL_GetTicks();
}

MapBlocks::MapBlocks()
{
    gRenderer= nullptr;
    MapBlocks(1, 1, gRenderer = nullptr, 5500, 2000, 0,0);
}

MapBlocks::MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gr, int cave_freq, int cave_width, int openAir, int openAirLength)
{
  gRenderer = gr;
  
    int i;
    for(i = 0; i<CEILING_N; i++){
        if(i>openAir && i<openAir+openAirLength && openAir+openAirLength<CEILING_N){
        ceiling_arr.push_back(WallBlock(i,false));
        }else{
        ceiling_arr.push_back(WallBlock(i,true));
        }
    }

    for (i = 0; i < BLOCKS_N; i++)
    {
        blocks_arr.push_back(Turret(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength)); // Initiating each Turret
    }
   

    for (i=0; i < STALAG_N; i++)
    {
        stalagm_arr.push_back(Stalagmite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the stalagmites
    }
    for (i=0; i < STALAG_N; i++)
    {
        stalagt_arr.push_back(Stalagtite(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, cave_freq, cave_width, openAir, openAirLength));//Initiate the stalagtites
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
    for (i = 0; i < blocks_arr.size(); i++)
    {
        blocks_arr[i].BLOCK_REL_X = blocks_arr[i].BLOCK_ABS_X - camX;
        blocks_arr[i].BLOCK_REL_Y = blocks_arr[i].BLOCK_ABS_Y - camY;
	}
    //ceiling
    for(i=0; i<CEILING_N; i++)
    {
        ceiling_arr[i].CEILING_REL_X = ceiling_arr[i].CEILING_ABS_X - camX;
    }


    for (i = 0; i < STALAG_N; i++)
    {
        stalagm_arr[i].STALAG_REL_X = stalagm_arr[i].STALAG_ABS_X - camX;
        stalagm_arr[i].STALAG_REL_Y = stalagm_arr[i].STALAG_ABS_Y-camY - WallBlock::block_side - stalagm_arr[i].STALAG_HEIGHT;
    }
    for (i = 0; i < STALAG_N; i++)
    {
        stalagt_arr[i].STALAG_REL_X = stalagt_arr[i].STALAG_ABS_X - camX;
        if(stalagt_arr[i].beenShot == 1){
            stalagt_arr[i].time_since_move = SDL_GetTicks() - stalagt_arr[i].last_move;
            if(stalagt_arr[i].STALAG_REL_Y <  stalagt_arr[i].terminalVelocityYValue){
                stalagt_arr[i].acceleration += 0.008 * stalagt_arr[i].time_since_move;
            }
            stalagt_arr[i].STALAG_REL_Y = stalagt_arr[i].STALAG_ABS_Y; //We should add an explosion upon reaching the botton of the cave
            stalagt_arr[i].STALAG_ABS_Y += stalagt_arr[i].acceleration; // maybe make it fall until it reaches halfway down instead when the tip collides
            stalagt_arr[i].last_move = SDL_GetTicks();
        }
        // stalagt_arr[i].STALAG_REL_Y = stalagt_arr[i].STALAG_ABS_Y-camY - WallBlock::block_side - stalagt_arr[i].STALAG_HEIGHT;
    }
	for (i = explosion_arr.size() - 1; i >= 0; i--)
	{
		explosion_arr[i].current_size = (double) explosion_arr[i].INITIAL_EXPLOSION_SIZE + ((SDL_GetTicks() - explosion_arr[i].explosion_time) * explosion_arr[i].EXPLOSION_SPEED) / 1000;
		explosion_arr[i].abs_x = explosion_arr[i].center_x - explosion_arr[i].current_size / 2;
		explosion_arr[i].abs_y = explosion_arr[i].center_y - explosion_arr[i].current_size / 2;
		explosion_arr[i].rel_x = explosion_arr[i].abs_x - camX;
		explosion_arr[i].rel_y = explosion_arr[i].abs_y - camY;
		explosion_arr[i].hitbox = {(int)explosion_arr[i].rel_x, (int)explosion_arr[i].rel_y, (int)explosion_arr[i].current_size, (int)explosion_arr[i].current_size};
		// If the explosion has reached its maximum size, get rid of it
		if (explosion_arr[i].current_size >= explosion_arr[i].FINAL_EXPLOSION_SIZE) {
			explosion_arr.erase(explosion_arr.begin() + i);
		}
	}
}

std::vector<Bullet*> MapBlocks::handleFiring(std::vector<Bullet*> bullets, int posX, int posY) {
	for (int i = 0; i < blocks_arr.size(); i++) {
		if (blocks_arr[i].enabled==true && blocks_arr[i].BLOCK_REL_X > 0 && blocks_arr[i].BLOCK_REL_Y > 0 && blocks_arr[i].BLOCK_REL_X <= 1280 && blocks_arr[i].BLOCK_REL_Y <= 720) {
			Bullet * newBullet = blocks_arr[i].handleFiring(posX, posY);
			if (newBullet != nullptr) {
				bullets.push_back(newBullet);
			}
		}
	}
	return bullets;
}

void MapBlocks::checkCollision(Player *p)
{
    
	int i;
    for (i = 0; i < BLOCKS_N; i++)
    {
        // If there's a collision, cancel the player's move
		if (blocks_arr[i].enabled==true && checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
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
        if (stalagm_arr[i].enabled==true && checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
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
        if (stalagt_arr[i].enabled==true && checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
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
    //ceiling
    for(i=0; i<CEILING_N; i++){
        if(ceiling_arr[i].enabled == true && (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side)))
        {
            p->undoXMove();
            p->undoYMove();

            if(checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT,ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side))
            {
                p->setPosX(std::max(ceiling_arr[i].CEILING_REL_X - p->PLAYER_WIDTH, 0));
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
		if (blocks_arr[i].enabled==true && checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
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
        if (stalagm_arr[i].enabled==true && checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
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

        if (stalagt_arr[i].enabled==true && checkCollide(e->getX(), e->getY(), e->getWidth(), e->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
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

// Returns true if the bullet hit something (and was therefore destroyed), and false otherwise
bool MapBlocks::checkCollision(Bullet *b)
{
    for (int i = blocks_arr.size() - 1; i >= 0; i--)
    {
        // If there's a collision with one of the planes, destroy the plane and the bullet
		if (checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT))
        {
			explosion_arr.push_back(Explosion(blocks_arr[i].BLOCK_ABS_X + blocks_arr[i].BLOCK_WIDTH / 2, blocks_arr[i].BLOCK_ABS_Y + blocks_arr[i].BLOCK_HEIGHT / 2, gRenderer));
            blocks_arr.erase(blocks_arr.begin() + i);
            return true;
        }
    }
    for (int i = 0; i < STALAG_N; i++)
    {
        // If there's a collision with a stalagmite or a stalagtite, detroy the bullet. The stalag will be fine; stalags are strong.
            //Not sure what we want to do with the stalagmites but reworked to stalagtites fall when shot
        if (stalagm_arr[i].enabled==true && checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT))
        {
            return true;
        }

        if (stalagt_arr[i].enabled==true && checkCollide(b->getX(), b->getY(), b->getWidth(), b->getHeight(), stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT))
        {
            stalagt_arr[i].beenShot = 1;
            stalagt_arr[i].last_move = SDL_GetTicks();
            return true;
        }
    }
	// Otherwise, the bullet didn't collide with anything and will survive
	return false;
}


void MapBlocks::render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer* gRenderer)
{
    int i;
    for (i = 0; i < blocks_arr.size(); i++)
    {
        // Only render the Turret if will be screen
        if (blocks_arr[i].enabled==true && blocks_arr[i].BLOCK_REL_X < SCREEN_WIDTH && blocks_arr[i].BLOCK_REL_Y < SCREEN_HEIGHT && blocks_arr[i].BLOCK_REL_Y >= WallBlock::block_side)
        {
            SDL_Rect fillRect = {blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, blocks_arr[i].BLOCK_WIDTH, blocks_arr[i].BLOCK_HEIGHT};
            SDL_RenderCopyEx(gRenderer, blocks_arr[i].sprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
            
        }
    }

    // Render floor
    for(i = 0; i < SCREEN_WIDTH; i+= WallBlock::block_side)
    {
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_Rect border1 = { i, SCREEN_HEIGHT - WallBlock::block_side - WallBlock::border, WallBlock::block_side, WallBlock::block_side - WallBlock::border};
        SDL_RenderFillRect(gRenderer, &border1);

       // SDL_Rect border2 = {i, 0, WallBlock::block_side, WallBlock::block_side + WallBlock::border};
       // SDL_RenderFillRect(gRenderer, &border2);

        SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
        SDL_Rect fillRectWall1 = { i, SCREEN_HEIGHT - WallBlock::block_side, WallBlock::block_side, WallBlock::block_side };
        SDL_RenderFillRect(gRenderer, &fillRectWall1);

       // SDL_Rect fillRectWall2 = {i, 0, WallBlock::block_side, WallBlock::block_side};
       // SDL_RenderFillRect(gRenderer, &fillRectWall);
    }

    //Render Ceiling
    for(i=0; i<CEILING_N; i++){

        if(ceiling_arr[i].CEILING_REL_X < SCREEN_WIDTH && ceiling_arr[i].CEILING_REL_Y < SCREEN_HEIGHT && ceiling_arr[i].enabled)
        {
            SDL_Rect fillRect = {ceiling_arr[i].CEILING_REL_X, ceiling_arr[i].CEILING_REL_Y, WallBlock::block_side, WallBlock::block_side};
            SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &fillRect);
        }
    }


    for (i = 0; i < STALAG_N; i++)
    {
        // Only render the Stalag if will be screen
        if (stalagm_arr[i].enabled==true && stalagm_arr[i].STALAG_REL_X >= -stalagt_arr[i].STALAG_HEIGHT && stalagm_arr[i].STALAG_REL_Y >= -stalagt_arr[i].STALAG_WIDTH && stalagm_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagm_arr[i].STALAG_REL_Y < SCREEN_HEIGHT)
        {
            SDL_Rect fillRect = {stalagm_arr[i].STALAG_REL_X, stalagm_arr[i].STALAG_REL_Y, stalagm_arr[i].STALAG_WIDTH, stalagm_arr[i].STALAG_HEIGHT};
            SDL_RenderCopyEx(gRenderer, stalagm_arr[i].sprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

    for (i = 0; i < STALAG_N; i++)
    {
        // Only render the Stalag if will be screen
        if (stalagt_arr[i].enabled==true && stalagt_arr[i].STALAG_REL_X >= -stalagt_arr[i].STALAG_WIDTH && stalagt_arr[i].STALAG_REL_Y >= -stalagt_arr[i].STALAG_HEIGHT && stalagt_arr[i].STALAG_REL_X < SCREEN_WIDTH && stalagt_arr[i].STALAG_REL_Y < SCREEN_HEIGHT && stalagt_arr[i].STALAG_REL_Y + stalagt_arr[i].STALAG_HEIGHT < SCREEN_HEIGHT + 35 - WallBlock::block_side){ // + 35 to have the stalags stick around a little after hittig the floor
            SDL_Rect fillRect = {stalagt_arr[i].STALAG_REL_X, stalagt_arr[i].STALAG_REL_Y, stalagt_arr[i].STALAG_WIDTH, stalagt_arr[i].STALAG_HEIGHT};
            SDL_RenderCopyEx(gRenderer, stalagt_arr[i].sprite, nullptr, &fillRect, 0.0, nullptr, SDL_FLIP_NONE);
        }
    }

	for (i = 0; i < explosion_arr.size(); i++) {
		SDL_RenderCopyEx(gRenderer, explosion_arr[i].sprite, nullptr, &explosion_arr[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
	}

}
