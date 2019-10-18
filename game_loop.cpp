#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MapBlocks.h"
#include "Player.h"
#include "Enemy.h"
#include "bullet.h"
#include "GameOver.h"
#include "CaveSystem.h"

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
double camY = LEVEL_HEIGHT - SCREEN_HEIGHT;

// Scrolling-related times so that scroll speed is independent of framerate
int time_since_horiz_scroll;
int last_horiz_scroll = SDL_GetTicks();

/*framerate timer
Uint32 fps_last_time = SDL_GetTicks();
Uint32 fps_cur_time = 0;
int framecount;
*/

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
	MapBlocks *blocks = new MapBlocks(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer);
	GameOver *game_over = new GameOver();
	CaveSystem *cave_system = new CaveSystem();

	//start enemy on left side behind player
	Enemy* en = new Enemy(100, SCREEN_HEIGHT/2, 125, 53, 200, 200, gRenderer);

	//initialize a vector of bullets
	std::vector<Bullet*> bullets;
	
	Bullet* newBullet;


	SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
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
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_7)
			{
				game_over->isGameOver = true;
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE) {
				if (player->canFire()) {
					bullets.push_back(new Bullet(player->getPosX() + player->PLAYER_WIDTH, player->getPosY() + player->PLAYER_HEIGHT/2,400));
				}
			}
			else {
				player->handleEvent(e);
			}
			if(game_over->isGameOver)
			{
				game_over->handleEvent(e, player, blocks,gRenderer);
			}
		}


		// Move player
		player->move(SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_HEIGHT, camY);

		//move enemy
		en->move(player->getPosX(), player->getPosY());
		newBullet = en->handleFiring();
		if (newBullet != nullptr) {
			bullets.push_back(newBullet);
		}
		
		//move the bullets
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
		}
		
		//Move Blocks and check collisions
		blocks->moveBlocks(camX, camY);
		blocks->checkCollision(player);
		blocks->checkCollision(en);
		for (int i = bullets.size() - 1; i >= 0; i--) {
			// If the bullet leaves the screen or hits something, it is destroyed
			bool destroyed;
			if (bullets[i]->getX() > SCREEN_WIDTH) {
				destroyed = true;
			}
			else {
				destroyed = blocks->checkCollision(bullets[i]);
			}
			if (destroyed) {
				bullets.erase(bullets.begin() + i);
			}
		}

		if((int) camX % 5500 == 0)
		{
			std::cout << "Creating Cave System" << std::endl;
			cave_system = new CaveSystem(camX, camY, SCREEN_WIDTH);
			cave_system->isEnabled = true;
		}
		
		if(cave_system->isEnabled)
		{
			cave_system->moveCaveBlocks(camX, camY);
			// cave_system->checkCollision();
		}

		// Clear the screen
		SDL_RenderClear(gRenderer);

		
		// Draw the player
		player->render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		// Draw the enemy
		en->renderEnemy(gRenderer);
		blocks->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);
		if (cave_system->isEnabled)
			cave_system->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

		//draw the bullets
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->renderBullet(gRenderer);
		}

/*
		framecount++;
		fps_cur_time=SDL_GetTicks();
		if (fps_cur_time - fps_last_time > 1000) {
			std::string fps= std::to_string(framecount / ((fps_cur_time - fps_last_time) / 1000.0));
			TTF_Font* Sans = TTF_OpenFont("Sans.ttf",14);
			SDL_Color Black = {000,000,000};
			SDL_Surface* fps_message = TTF_RenderText_Solid(Sans, fps.c_str(), Black);
			SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, fps_message);
			SDL_Rect message_rect = {0,0,75,20};
			SDL_RenderCopy(gRenderer, message,NULL, &message_rect);

			// reset
			fps_last_time = fps_cur_time;
			framecount = 0;
		}
*/
		if(game_over->isGameOver)
		{
			game_over->stopGame(player, blocks);
			game_over->render(gRenderer);
		}
		


		SDL_RenderPresent(gRenderer);
	}

	// Out of game loop, clean up
	close();
}
