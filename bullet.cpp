#include "bullet.h"

	Bullet::Bullet(int x, int y, int vel) :xPos{x}, yPos{y},width{5},height{5}{
		bullet_sprite = {xPos, yPos,width, height};
		hitbox = bullet_sprite;
		xVel = vel;
	};

	void Bullet::renderBullet(SDL_Renderer* gRenderer){
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &bullet_sprite);
	}

	void Bullet::move(){
		xPos -= xVel;
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