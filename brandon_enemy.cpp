#include <SDL.h>
#include "Enemy.h"
#include <iostream> // for testing


Enemy::Enemy(int x, int y) :xPos{x}, yPos{y},width{20},height{20},xVelo{2},yVelo{0}{
  enemy_sprite = {xPos, yPos, width, height};
  enemy_hitbox = enemy_sprite;
  setyVelo(0);
};

void Enemy::renderEnemy(SDL_Renderer* gRenderer){
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(gRenderer, &enemy_sprite);
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
 last_move = SDL_GetTicks();
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

