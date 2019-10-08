#include "bullet.h"
#include <SDL.h>
#include "Enemy.h"



    Enemy::Enemy(int x, int y) :xPos{static_cast<double>(x)}, yPos{static_cast<double>(y)},width{20},height{20},xVelo{0},yVelo{0}{
      enemy_sprite = {static_cast<int>(xPos), static_cast<int>(yPos), width, height};
      enemy_hitbox = enemy_sprite;
      time_since_move = SDL_GetTicks();
    }

    void Enemy::renderEnemy(SDL_Renderer* gRenderer){
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &enemy_sprite);
    }

    void Enemy::move(int player_x, int player_y)
    {

      time_since_move = SDL_GetTicks() - last_move;
      yPos += (double) (yVelo * time_since_move) / 1000;
      if(yPos<=0 || yPos>=720-height){
        yVelo = -yVelo;
      }
      enemy_sprite = {static_cast<int>(xPos),static_cast<int>(yPos),width,height};
      enemy_hitbox = enemy_sprite;
      last_move = SDL_GetTicks();


      // move the enemy to the right if the player is moving right
      // want to "collide" when the enemy hits us
      if(xPos < (player_x - width))
      xPos += xVelo;

      // move the enemy to the right if the player is moving right
      // want to "collide" when the enemy hits us
      if(xPos > (player_x + width))
      xPos -= xVelo;

      // move the enemy down while the player is moving down
      if(yPos < (player_y - height))
      yPos -= yVelo;

      // move the enemy up while the player is moving up 
      if(yPos > (player_y + height))
      yPos += yVelo;

      enemy_sprite = {static_cast<int>(xPos),static_cast<int>(yPos),width,height};
    }


    int Enemy::getX(){
      return static_cast<int>(xPos);
    }

    int Enemy::getY(){
      return static_cast<int>(yPos);
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


    Bullet* Enemy::shoot()
    {
        Bullet* b = new Bullet(xPos+width+5,yPos+height/2,-300);

        return b;
    }