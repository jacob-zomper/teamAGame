
#include "bullet.h"
#include <iostream>
#include <SDL.h>

	Bullet::Bullet(int x, int y,int vel) :xPos{(double)x}, yPos{(double)y},width{BULLET_SIZE},height{BULLET_SIZE}{
		bullet_sprite = {(int)xPos,(int)yPos,width, height};
		hitbox = bullet_sprite;
		xVel = vel;
		last_move = SDL_GetTicks();
	};

	void Bullet::renderBullet(SDL_Renderer* gRenderer){
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &bullet_sprite);
	}

	void Bullet::move(){
		time_since_move = SDL_GetTicks() - last_move;
		xPos += ((double) time_since_move * xVel) / 1000;
		bullet_sprite ={(int)xPos,(int)yPos,width,height};
		hitbox = bullet_sprite;
		last_move = SDL_GetTicks();
	}

	int Bullet::getX(){
		return xPos;
	}

	int Bullet::getY(){
		return yPos;
	}

	int Bullet::getWidth(){
		return width;
	}

	int Bullet::getHeight(){
		return height;
	}

	SDL_Rect* Bullet::getHitbox(){
		return &hitbox;
	}
