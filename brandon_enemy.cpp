#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Enemy.h"

SDL_Texture* Enemy::loadImage(std::string fname, SDL_Renderer *gRenderer) {
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

Enemy::Enemy(int x, int y, SDL_Renderer *gRenderer) :xPos{x}, yPos{y},width{125},height{53},xVelo{120},yVelo{0}{
  enemy_sprite = {xPos, yPos, width, height};
  enemy_hitbox = enemy_sprite;
  setyVelo(0);
  sprite1 = loadImage("sprites/EnemyPlane1.png", gRenderer);
  sprite2 = loadImage("sprites/EnemyPlane3.png", gRenderer);
};

void Enemy::renderEnemy(SDL_Renderer* gRenderer){
	// Alternates through the two sprites every ANIMATION_FREQ ticks
	if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
		SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &enemy_sprite, 0.0, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &enemy_sprite, 0.0, nullptr, SDL_FLIP_NONE);
	}
}

void Enemy::move(int player_x, int player_y)
{
  
  time_since_move = SDL_GetTicks() - last_move;
 // move the enemy to the right if the player is moving right
 // want to "collide" when the enemy hits us
 if(xPos < (player_x - width))
   xPos += (double) (xVelo * time_since_move) / 1000;
 
 // move the enemy to the right if the player is moving right
 // want to "collide" when the enemy hits us
 if(xPos > (player_x + width))
   xPos -= (double) (xVelo * time_since_move) / 1000;
 
// move the enemy down while the player is moving down
if(yPos < (player_y - height))
  yPos -= (double) (yVelo * time_since_move) / 1000;

// move the enemy up while the player is moving up 
if(yPos > (player_y + height))
  yPos += (double) (yVelo * time_since_move) / 1000;

 enemy_sprite = {xPos,yPos,width,height};

 //printf("%d\n", checkCollision(player_x, player_y));
 last_move = SDL_GetTicks();
}

bool Enemy::checkCollision(int player_x,int player_y)
 {
    if(xPos < (player_x - width) || xPos > (player_x + width))
      return true;
    
    if(yPos < (player_y - height) || yPos > (player_y + width))
      return true;

    return false;
 }

int Enemy::getX(){
  return xPos;
}

int Enemy::getY(){
  return yPos;
}

void Enemy::setyVelo(int y){
  yVelo = y;
}

void Enemy::setxVelo(int x) {
  xVelo = x;
}

SDL_Rect* Enemy::getHitbox(){
  return &enemy_hitbox;
}

