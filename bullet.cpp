




class Bullet
{


public:

	Bullet(int x, int y) :xPos{x}, yPos{y},width{2},height{2}{
		bullet_sprite = {xPos, yPos,width, height};
		xVel = 5;
	};

	void renderBullet(SDL_Renderer* gRenderer){
		// Draw box
		// Clear black
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);
		// Cyan box
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(gRenderer, &bullet_sprite);
		SDL_RenderPresent(gRenderer);
	}

	void move(){
		xPos -= xVel;
		bullet_sprite ={xPos,yPos,width,height};
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


};