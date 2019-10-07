#include <SDL.h>
#include "Enemy.h"
#include <iostream> // for testing


Enemy::Enemy(int x, int y) :xPos{x}, yPos{y},width{20},height{20},xVelo{0},yVelo{0}{
  enemy_sprite = {xPos, yPos, width, height};
  enemy_hitbox = enemy_sprite;
};

void Enemy::renderEnemy(SDL_Renderer* gRenderer){
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(gRenderer, &enemy_sprite);
}

void Enemy::move(int player_x, int player_y)
{
  /*
   Want to follow the player around the map by using the player's position
  1. Get player's position and print to the screen where the player is moving
  
  */
 //printf("in the move fuction");
 printf("Here is the players position: %d %d\n", player_x, player_y);
 enemy_sprite = {xPos,yPos,width,height};
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

