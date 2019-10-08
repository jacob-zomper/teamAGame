
#include "bullet.h"
# include <SDL.h>


	Bullet::Bullet(int x, int y,int vel) :xPos{x}, yPos{y},width{5},height{5}{
		bullet_sprite = {xPos, yPos,width, height};
		hitbox = bullet_sprite;
		xVel = vel;
		time_since_move = SDL_GetTicks();
	};

	void Bullet::renderBullet(SDL_Renderer* gRenderer){
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &bullet_sprite);
	}

	void Bullet::move(){
		time_since_move = SDL_GetTicks() - last_move;
		xPos -= (double) (time_since_move * xVel) / 1000;
		bullet_sprite ={xPos,yPos,width,height};
		hitbox = bullet_sprite;
	}

	int Bullet::getX(){
		return xPos;
	}

	int Bullet::getY(){
		return yPos;
	}

	SDL_Rect* Bullet::getHitbox(){
		return &hitbox;
	}
