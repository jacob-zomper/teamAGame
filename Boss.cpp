#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "Boss.h"
#include "bullet.h"
#include "missile.h"

SDL_Texture* Boss::loadImage(std::string fname, SDL_Renderer *gRenderer) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
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

Boss::Boss(int x, int y, int xvel, int yvel, int diff, SDL_Renderer *gRenderer): xPos{(double) x}, yPos{(double) y},maxXVelo{xvel},maxYVelo{yvel}{
  boss_sprite = {(int) xPos, (int) yPos, WIDTH, HEIGHT};
  boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
  boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
  last_move = SDL_GetTicks();
  last_shot_middle = SDL_GetTicks() - FIRING_FREQ;
  last_shot_down = last_shot_middle;
  last_shot_up = last_shot_middle;
  up = false;
  mvmt = false;
  maxXVelo = 200;
  maxYVelo = 200;
  //sprite1 = loadImage(name, gRenderer);
}

// IF YOU CREATE ANY POINTERS, DELETE THEM IN THIS METHOD
Boss::~Boss() {
	
}


void Boss::renderBoss(int SCREEN_WIDTH, SDL_Renderer* gRenderer){
    if(xPos<SCREEN_WIDTH){
      //SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &boss_sprite, 0, nullptr, SDL_FLIP_NONE);
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &boss_hitbox_top);
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
      SDL_RenderFillRect(gRenderer, &boss_hitbox_bottom);
      boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
      boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
    }
}

void Boss::move(int SCREEN_WIDTH){
	xVelo = 0;
	if (yVelo == 0) {
		yVelo = maxYVelo;
	}
	else if (yVelo > 0 && yPos > MAX_DOWN) {
		yVelo = -maxYVelo;
	}
	else if (yVelo < 0 && yPos < MAX_UP) {
		yVelo = maxYVelo;
	}
	time_since_move = SDL_GetTicks() - last_move;
	xPos += (double) (xVelo * time_since_move)/1000;
	yPos += (double) (yVelo * time_since_move)/1000;
	boss_sprite = {(int)xPos,(int)yPos,WIDTH,HEIGHT};
	boss_hitbox_bottom = {(int) xPos, (int) (yPos+(HEIGHT/2)), WIDTH, HEIGHT/2};
	boss_hitbox_top = {(int) (xPos+(WIDTH/4)), (int) yPos, WIDTH/2, HEIGHT};
	last_move = SDL_GetTicks();
}

// Boss::~Boss(){
//   //undo image
// }

bool Boss::checkCollisionBullet(int bullX, int bullY, int bullW, int bullH) {
	return checkCollide(bullX, bullY, bullW, bullH, xPos, yPos, WIDTH, HEIGHT);
}

bool Boss::checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

Missile* Boss::handleFiringMiddle(){
  int damage = 500;
  int blast_radius = 150;
  return nullptr;
}

Bullet* Boss::handleFiringUp(){
  return nullptr;
}

Bullet* Boss::handleFiringDown(){
  return nullptr;
}

void Boss::hit(int d){
  if (health - d < 0)
    health = 0;
  else
    health -= 0;
}

int Boss::getX(){
  return (int) xPos;
}

int Boss::getY(){
  return (int) yPos;
}

int Boss::getWidth() {
  return WIDTH;
}

int Boss::getHeight() {
  return HEIGHT;
}

int Boss::getHealth(){
  return health;
}

void Boss::moveLeft() {
	time_since_move = SDL_GetTicks() - last_move;
	xPos -= (double) (maxXVelo * time_since_move) / 1000;
	last_move = SDL_GetTicks();
}
