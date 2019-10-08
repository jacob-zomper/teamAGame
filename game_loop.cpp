#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "MapBlocks.h"
#include "Player.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int LEVEL_WIDTH = 100000;
constexpr int LEVEL_HEIGHT = 2000;
constexpr int SCROLL_SPEED = 420;

// Function declarations
bool init();
SDL_Texture* loadImage(std::string fname);
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

// X and y positions of the camera
double camX = 0;
double camY = 640;

// Scrolling-related times so that scroll speed is independent of framerate
int time_since_horiz_scroll;
int last_horiz_scroll = SDL_GetTicks();


bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	gWindow = SDL_CreateWindow("TeamAGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

SDL_Texture* loadImage(std::string fname) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
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
	Player * player = new Player(SCREEN_WIDTH/4 - Player::PLAYER_WIDTH/2, SCREEN_HEIGHT/2 - Player::PLAYER_HEIGHT/2, gRenderer);
	MapBlocks *blocks = new MapBlocks(LEVEL_WIDTH, LEVEL_HEIGHT);

	SDL_Event e;
	bool gameon = true;

	while(gameon) {

		// Scroll to the side, unless the end of the level has been reached
		time_since_horiz_scroll = SDL_GetTicks() - last_horiz_scroll;
		camX += (double) (SCROLL_SPEED * time_since_horiz_scroll) / 1000;
		if (camX > LEVEL_WIDTH - SCREEN_WIDTH) {
			camX = LEVEL_WIDTH - SCREEN_WIDTH;
		}
		last_horiz_scroll = SDL_GetTicks();

		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameon = false;
			}

			player->handleEvent(e);


		}

		// Move player
		player->move(SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_HEIGHT, camY);

		//Move Blocks
		blocks->moveBlocksAndCheckCollision(player, camX, camY);

		// Clear the screen
		SDL_RenderClear(gRenderer);

		// Draw the player
		player->render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		blocks->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);


		SDL_RenderPresent(gRenderer);
	}

	// Out of game loop, clean up
	close();
}
