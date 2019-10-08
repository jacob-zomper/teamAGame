#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "Enemy.h"
#include "bullet.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;

// Function declarations
bool init();
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	gWindow = SDL_CreateWindow("Hello world!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	// Adding VSync to avoid absurd framerates
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == nullptr) {
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return  false;
	}

	// Set renderer draw/clear color
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

	return true;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

// void moveDummy(int* y, int* yVel){
//
// 	*y += *yVel;
//
// 	if(*y==0 || *y==SCREEN_HEIGHT-50){
// 		*yVel = -*yVel;
// 	}
// }

int main() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}

	Bullet* b = new Bullet(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 300);
	Enemy* en = new Enemy(50, SCREEN_HEIGHT/2, 125, 53, 200, 200, gRenderer);
	en->setyVelo(-300);

	//variables for dummy
	// int x = 50;
	// int y = SCREEN_HEIGHT/2;
	// int xVel=0;
	// int yVel=-300;


	SDL_Event e;
	bool gameon = true;
	bool shootOnce = true;
	while(gameon) {
		while(SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					gameon = false;
				}
		}

		//move the bullet
		//b->move();
		//moveDummy(&y,&yVel);
		en->move();


		//clear the screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//render the bullet
		//b->renderBullet(gRenderer);


		//render the dummy box
		// SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		// SDL_Rect dummy = {x,y,50,50};
		// SDL_RenderFillRect(gRenderer, &dummy);
		// //put it on the screen
		
		
		if(shootOnce)
		{
			en->shoot();
			shootOnce = false;
		}

		en->renderEnemy(gRenderer);
		SDL_RenderPresent(gRenderer);

		// if the bullet reaches the end of the screen
		// destroy it and make a new bullet




	}
	//out of game loop, clean up
	close();
}
