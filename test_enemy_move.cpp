#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "MapBlocks.h"
#include "Player.h"
#include "Enemy.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int LEVEL_WIDTH = 100000;
constexpr int LEVEL_HEIGHT = 2000;
constexpr int SCROLL_SPEED = 7;

// Function declarations
bool init();
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
// X and y positions of the camera
int camX = 0;
int camY = 640;


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
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

int main() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}
	
	//Start the player on the left side of the screen
	Player * player = new Player(SCREEN_WIDTH/4 - Player::PLAYER_WIDTH/2, SCREEN_HEIGHT/2 - Player::PLAYER_HEIGHT/2);
	//MapBlocks *blocks = new MapBlocks(LEVEL_WIDTH, LEVEL_HEIGHT);
	Enemy * en = new Enemy(SCREEN_WIDTH, SCREEN_HEIGHT);
	en->setyVelo(-5);
	

	SDL_Event e;
	bool gameon = true;

	while(gameon) {

		// // Scroll SCROLL_SPEED pixels to the side, unless the end of the level has been reached
		// camX += SCROLL_SPEED;
		// if (camX > LEVEL_WIDTH - SCREEN_WIDTH) {
		// 	camX = LEVEL_WIDTH - SCREEN_WIDTH;
		// }

		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameon = false;
			}

			player->handleEvent(e);


		}

		// Move player
		player->move(SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_HEIGHT, camY);

		// Move the enemy
		en->move(player->getPosX(), player->getPosY());

		//Move Blocks
		//blocks->moveBlocksAndCheckCollision(player, camX, camY);

		// Clear the screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		// Draw the player
		player->render(gRenderer);
		en->renderEnemy(gRenderer);
		//blocks->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);


		SDL_RenderPresent(gRenderer);

		// Scroll 5 pixels to the side, unless the end of the level has been reached
		camX += 10;
		if (camX > LEVEL_WIDTH - SCREEN_WIDTH) {
			camX = LEVEL_WIDTH - SCREEN_WIDTH;
		}
	}

	// Out of game loop, clean up
	close();
}
