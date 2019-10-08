#include <SDL.h>
#include "Enemy.h"


Enemy::Enemy(int x, int y) :xPos{x}, yPos{y},width{20},height{20},xVelo{0},yVelo{0}{
  enemy_sprite = {xPos, yPos, width, height};
  enemy_hitbox = enemy_sprite;
  time_since_move = SDL_GetTicks();
};

void Enemy::renderEnemy(SDL_Renderer* gRenderer){
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(gRenderer, &enemy_sprite);
}

void Enemy::move(){
  time_since_move = SDL_GetTicks() - last_move;
  yPos += (double) (yVelo * time_since_move) / 1000;
  if(yPos<=0 || yPos>=720-height){
    yVelo = -yVelo;
  }
  enemy_sprite = {xPos,yPos,width,height};
  enemy_hitbox = enemy_sprite;
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

