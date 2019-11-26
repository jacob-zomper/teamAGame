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
  time_since_pattern = SDL_GetTicks();
  last_shot_missile = SDL_GetTicks() - FIRING_FREQ;
  last_shot_down = last_shot_missile;
  last_shot_up = last_shot_missile;
  upright = false;
  upleft = false;
  downleft = false;
  downright = false;
  oneActive = false;
  ur_fire = false;
  ul_fire = false;
  dl_fire = false;
  dr_fire = false;
  maxXVelo = 200;
  maxYVelo = 200;
  last_pattern = 0;
  corner_location = 0;
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
  time_since_pattern = SDL_GetTicks() - last_pattern;
  if (time_since_pattern >= PATTERNONEFREQ){
    patternOne(SCREEN_WIDTH);
  }else{
      if (yVelo == 0) {
		      yVelo = maxYVelo;
	    }
	    else if (yVelo > 0 && yPos > MAX_DOWN) {
		      yVelo = -maxYVelo;
	    }
	    else if (yVelo < 0 && yPos < MAX_UP) {
		      yVelo = maxYVelo;
	    }
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

std::vector<Missile*> Boss::handleFiringMissile(std::vector<Missile*> missiles ,int x, int y, SDL_Renderer* gRenderer){
  int damage = 500;
  int blast_radius = 150;
  time_since_shot_missile = SDL_GetTicks() - last_shot_missile;
  Missile* m = nullptr;
  if(oneActive){
    int xDist = x - xPos;
    int yDist = y - (yPos+(HEIGHT/2));
    double math = (double)xDist / sqrt(xDist * xDist + yDist * yDist) * 400;
    double math2 = ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400;
    if(!ul_fire && corner_location == 1){
      m = new Missile(damage, blast_radius, xPos, yPos+HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      ul_fire = true;
    }else if (!ur_fire && corner_location == 2){
      m = new Missile(damage, blast_radius, xPos+WIDTH, yPos+HEIGHT, ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      ur_fire = true;
    }else if (!dl_fire && corner_location == 3){
      m = new Missile(damage, blast_radius, xPos+WIDTH, yPos+(HEIGHT/2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      dl_fire = true;
    }else if (!dr_fire && corner_location == 4){
      m = new Missile(damage, blast_radius, xPos, yPos+(HEIGHT/2), ((double)xDist / sqrt(xDist * xDist + yDist * yDist)) * 400, ((double)yDist / sqrt(xDist * xDist + yDist * yDist)) * 400, loadImage("sprites/missile.png", gRenderer), gRenderer);
      dr_fire = true;
    }
    if (m != nullptr)
      missiles.push_back(m);
  }
  return missiles;
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
    health -= d;
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

void Boss::patternOne(int SCREEN_WIDTH){
  xVelo = 0;
  yVelo = 0;
  if(!upright){
    if (yPos > MAX_UP)
      yVelo = -maxYVelo;
    else{
      yVelo = 0;
      oneActive = true;
      corner_location = 1;
    }

    if (time_since_pattern - PATTERNONEFREQ >= corner_delay){
      upright = true;
      oneActive = false;
    }

  }else if(!upleft){

    if (xPos > 50){
      xVelo = -(maxXVelo*2);
      yVelo = 0;
    }else{
      xVelo = 0;
      yVelo = 0;
      oneActive = true;
      corner_location = 2;
    }

    if ((time_since_pattern - PATTERNONEFREQ) >= corner_delay*2){
      upleft = true;
      oneActive = false;
    }

  }else if(!downleft){
    if (yPos < MAX_DOWN){
      xVelo = 0;
      yVelo = maxYVelo;
    }else{
      xVelo = 0;
      yVelo = 0;
      oneActive = true;
      corner_location = 3;
    }

      if ((time_since_pattern-PATTERNONEFREQ) >= corner_delay*3){
        downleft = true;
        oneActive = false;
      }

  }else if(!downright){
    if (xPos < SCREEN_WIDTH - WIDTH - 50){
      xVelo = (maxXVelo*2);
      yVelo = 0;
    }else{
      xVelo = 0;
      yVelo = 0;
      oneActive = true;
      corner_location = 4;
    }

    if (time_since_pattern-PATTERNONEFREQ >= corner_delay*4)
      downright = true;
  }

  if(downright){
    upright = false;
    upleft = false;
    downleft = false;
    downright = false;
    ur_fire = false;
    ul_fire = false;
    dl_fire = false;
    dr_fire = false;
    last_pattern = SDL_GetTicks();
    oneActive = false;
    corner_location = 0;
  }
}
