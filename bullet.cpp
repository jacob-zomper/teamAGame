#include "bullet.h"




class Bullet
{


public:

	Bullet(int x, int y, int vel) :xPos{x}, yPos{y},width{5},height{5}{
		bullet_sprite = {xPos, yPos,width, height};
		hitbox = bullet_sprite;
		xVel = vel;
	};

	void renderBullet(SDL_Renderer* gRenderer){
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &bullet_sprite);
	}

	void move(){
		xPos -= xVel;
		bullet_sprite ={xPos,yPos,width,height};
		hitbox = bullet_sprite;
	}

	int getX(){
		return xPos;
	}

	int getY(){
		return yPos;
	}

	SDL_Rect* getHitbox(){
		return &hitbox;
	}





private:
	//define's size of bullet
	const int width;
	const int height;

	// x and y position of bullet
	//y will never be updated
	int xPos;
	int yPos;

	// velocity of bullet
	// y velocity will always be 0
	int xVel;

	SDL_Rect bullet_sprite;
	SDL_Rect hitbox;	


};