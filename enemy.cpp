#include "bullet.h"
#include <SDL.h>
#include "Enemy.h"

class Enemy
{

  public:


    Enemy::Enemy(int x, int y) :xPos{x}, yPos{y},width{20},height{20},xVelo{0},yVelo{0}{
      enemy_sprite = {xPos, yPos, width, height};
      enemy_hitbox = enemy_sprite;
    }

    void Enemy::renderEnemy(SDL_Renderer* gRenderer){
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &enemy_sprite);
    }

    void Enemy::move(){
      yPos += yVelo;
      if(yPos==0 || yPos==720-height){
        yVelo = -yVelo;
      }
      enemy_sprite = {xPos,yPos,width,height};
      enemy_hitbox = enemy_sprite;
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

    void Enemy::shoot(Bullet* b){
      int shotX = xPos+(width);
      int shotY = yPos-(height/2);

      b= new Bullet(shotX,shotY,-10);
    }

  private:

    //Position and size of the enemy sprite on screen
    int xPos;
    int yPos;
    const int width;
    const int height;

    //Velocity of the enemy
    int xVelo;
    int yVelo;


    //defines the enemy asset
    SDL_Rect enemy_sprite;
    //defines the hitbox of the enemy
    SDL_Rect enemy_hitbox;
}

