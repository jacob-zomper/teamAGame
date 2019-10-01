#define SDL_MAIN_HANDLED
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int LEVEL_WIDTH = 10000;
constexpr int LEVEL_HEIGHT = 2000;
constexpr int BOX_WIDTH = 20;
constexpr int BOX_HEIGHT = 20;

// Function declarations
bool init();
void close();

// Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
// X and y positions of the camera
int camX = 0;
int camY = 640;

class MapBlocks
{
	class Block
	{
	public:
		// absolute coordinates of each block
		int BLOCK_ABS_X;
		int BLOCK_ABS_Y;

		// coordinates of each block relative to camera
		int BLOCK_REL_X;
		int BLOCK_REL_Y;

		int BLOCK_SPRITE; // Map to which sprite image this block will use.


		Block()
		{
			BLOCK_ABS_X = rand() % LEVEL_WIDTH;
			BLOCK_ABS_Y = rand() % LEVEL_HEIGHT;

			// These should be the same first
			BLOCK_REL_X = BLOCK_ABS_X;
			BLOCK_REL_Y = BLOCK_ABS_Y;
		}
	};

public:
	static const int BLOCKS_N = 10000;
	static const int BLOCK_HEIGHT = 20;
	static const int BLOCK_WIDTH = 20;
	Block *blocks_arr;

	MapBlocks()
	{
		blocks_arr = new Block[BLOCKS_N];
		int i;
		for (i = 0; i < BLOCKS_N; i++)
		{
			blocks_arr[i] = Block(); // Initiating each block
		}
	}

	void moveBlocks()
	{
		int i;
		for (i = 0; i < BLOCKS_N; i++)
		{
			blocks_arr[i].BLOCK_REL_X = blocks_arr[i].BLOCK_ABS_X - camX;
			blocks_arr[i].BLOCK_REL_Y = blocks_arr[i].BLOCK_ABS_Y - camY;
		}
	}

	void render()
	{
		//Draw player as cyan rectangle
		int i;
		for (i = 0; i < BLOCKS_N; i++)
		{
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_Rect fillRect = {blocks_arr[i].BLOCK_REL_X, blocks_arr[i].BLOCK_REL_Y, BLOCK_WIDTH, BLOCK_HEIGHT};
			SDL_RenderFillRect(gRenderer, &fillRect);
		}

	}

};

class Player
{
	public:
		//The dimensions of the player
        static const int PLAYER_WIDTH = 20;
        static const int PLAYER_HEIGHT = 20;

        //Maximum axis velocity of the player
        static const int MAX_PLAYER_VEL = 5;

        //Initializes the variables
        Player(int xPos, int yPos)
		{
			x_pos = xPos;
			y_pos = yPos;
		}

        //Takes key presses and adjusts the player's velocity
        void handleEvent( SDL_Event& e )
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						y_vel -= MAX_PLAYER_VEL;
						break;

					case SDLK_a:
						x_vel -= MAX_PLAYER_VEL;
						break;

					case SDLK_s:
						y_vel += MAX_PLAYER_VEL;
						break;

					case SDLK_d:
						x_vel += MAX_PLAYER_VEL;
						break;
				}
			} else if (e.type == SDL_KEYUP) {
					switch(e.key.keysym.sym) {
						case SDLK_w:
							y_vel += MAX_PLAYER_VEL;
							break;

						case SDLK_a:
							x_vel += MAX_PLAYER_VEL;
							break;

						case SDLK_s:
							y_vel -= MAX_PLAYER_VEL;
							break;

						case SDLK_d:
							x_vel -= MAX_PLAYER_VEL;
							break;
					}
			}
		}

        //Moves the player
        void move()
		{
			if (y_vel > MAX_PLAYER_VEL)
				y_vel = MAX_PLAYER_VEL;
			else if (y_vel < -MAX_PLAYER_VEL)
				y_vel = -MAX_PLAYER_VEL;
			if (x_vel > MAX_PLAYER_VEL)
				x_vel = MAX_PLAYER_VEL;
			else if (x_vel < -MAX_PLAYER_VEL)
				x_vel = -MAX_PLAYER_VEL;

			x_pos += x_vel;
			y_pos += y_vel;

			// Move the player horizontally
			if (x_pos < 0) {
				x_pos = 0;
				x_vel = 0;
			}
			else if (x_pos > SCREEN_WIDTH - PLAYER_WIDTH) {
				x_pos = SCREEN_WIDTH - PLAYER_WIDTH;
				x_vel = 0;
			}

			// Move the player vertically.
			// If they are near the top of the screen, scroll up
			if (y_pos < SCREEN_HEIGHT / 10 && camY > 0) {
				y_pos = SCREEN_HEIGHT / 10;
				camY += y_vel;
			}
			// Stop the player if they hit the top of the level
			else if (y_pos < 0) {
				y_pos = 0;
				y_vel = 0;
			}
			// If they are near the bottom of the screen, scroll down
			else if (y_pos > (9 * SCREEN_HEIGHT) / 10 - PLAYER_HEIGHT && camY < LEVEL_HEIGHT - SCREEN_HEIGHT) {
				y_pos = (9 * SCREEN_HEIGHT) / 10 - PLAYER_HEIGHT;
				camY += y_vel;
			}
			// Stop the player if they hit the bottom
			else if (y_pos > SCREEN_HEIGHT - PLAYER_HEIGHT) {
				y_pos = SCREEN_HEIGHT - PLAYER_HEIGHT;
				y_vel = 0;
			}

			if (camY < 0) {
				camY = 0;
			}
			else if (camY > LEVEL_HEIGHT - SCREEN_HEIGHT) {
				camY = LEVEL_HEIGHT - SCREEN_HEIGHT;
			}
		}

        //Shows the player on the screen relative to the camera
        void render()
		{
			//Draw player as cyan rectangle
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
			SDL_Rect fillRect = {x_pos, y_pos, BOX_WIDTH, BOX_HEIGHT};
			SDL_RenderFillRect(gRenderer, &fillRect);
		}

        //Position accessors
        int getPosX();
        int getPosY();
	private:
		//The X and Y offsets of the player (ON SCREEN)
        int x_pos, y_pos;

        //The velocity of the player
        int x_vel, y_vel;
};

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
	Player * player = new Player(SCREEN_WIDTH/4 - BOX_WIDTH/2, SCREEN_HEIGHT/2 - BOX_HEIGHT/2);
	MapBlocks *blocks = new MapBlocks();

	SDL_Event e;
	bool gameon = true;
	while(gameon) {
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				gameon = false;
			}
			
			player->handleEvent(e);


		}

		// Move player
		player->move();

		//Move Blocks
		blocks->moveBlocks();

		// Clear the screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		// Draw the player
		player->render();
		blocks->render();


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
