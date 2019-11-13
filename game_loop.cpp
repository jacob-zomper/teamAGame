#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <SDL.h>
#include <time.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "MapBlocks.h"
#include "Player.h"
#include "Enemy.h"
#include "bullet.h"
#include "GameOver.h"
#include "StartScreen.h"
#include "CaveSystem.h"
#include "Text.h"
#include "Kamikaze.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int LEVEL_WIDTH = 100000;
constexpr int LEVEL_HEIGHT = 2000;
constexpr int SCROLL_SPEED = 420;
constexpr int FLOOR_BOTTOM = 720-79;
constexpr int ROOF_TOP = 73;

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

Player * player;
MapBlocks *blocks;
GameOver *game_over;
StartScreen *start_screen;
CaveSystem *cave_system;
std::vector<Bullet*> bullets;
std::vector<Missile*> missiles;
Enemy* en;
Kamikaze* kam;
bool caveCounterHelp = false;

// Music stuff
Mix_Music *trash_beat = NULL;
Mix_Music* song = NULL;
int current_track = -1;


// Scrolling-related times so that scroll speed is independent of framerate
int time_since_horiz_scroll;
int last_horiz_scroll = SDL_GetTicks();

//framerate timer
Uint32 fps_last_time = SDL_GetTicks();
Uint32 fps_cur_time = 0;
int framecount;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
	}

	if(TTF_Init()==-1){
		std::cout<<"TTF could not initialize";
		return false;
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

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return false;
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

Mix_Music* loadMusic(std::string fname) {
	Mix_Music* newMusic = Mix_LoadMUS(fname.c_str());

	if( newMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return nullptr;
    }
	return newMusic;
}

void close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	Mix_FreeMusic(trash_beat);

	gWindow = nullptr;
	gRenderer = nullptr;
	TTF_Quit();

	// Quit SDL subsystems
	SDL_Quit();
	exit(0);
}

// Function that prepares for enemy movement. Put in a separate method to avoid cluttering the main loop
void moveEnemy(Enemy * en, Kamikaze* kam) {
	int playerX = player->getPosX() + player->PLAYER_WIDTH/2;
	int playerY = player->getPosY() + player->PLAYER_HEIGHT/2;
	std::vector<int> bulletX;
	std::vector<int> bulletY;
	std::vector<int> bulletVelX;
	std::vector<int> bulletVelY;
	std::vector<int> stalagmX;
	std::vector<int> stalagmH;
	std::vector<int> stalagtX;
	std::vector<int> stalagtH;
	std::vector<int> turretX;
	std::vector<int> turretBottom;
	std::vector<int> turretH;
	// std::vector<int> kamiX;
	// std::vector<int> kamiY;
	// std::vector<FlyingBlock> kamikazes = blocks->getKamikazes();
	for (int i = 0; i < bullets.size(); i++) {
		bulletX.push_back(bullets[i]->getX());
		bulletY.push_back(bullets[i]->getY());
		bulletVelX.push_back(bullets[i]->getXVel());
		bulletVelY.push_back(bullets[i]->getYVel());
	}
	std::vector<Stalagmite> stalagmites = blocks->getStalagmites();
	std::vector<Stalagtite> stalagtites = blocks->getStalagtites();
	std::vector<Turret> turrets = blocks->getTurrets();
	for (int i = 0; i < stalagmites.size(); i++) {
		if (stalagmites[i].STALAG_ABS_X - camX > 0 && stalagmites[i].STALAG_ABS_X - camX < SCREEN_WIDTH) {
			stalagmX.push_back(stalagmites[i].STALAG_ABS_X - camX);
			stalagmH.push_back(stalagmites[i].STALAG_HEIGHT + WallBlock::block_side);
		}
	}
	for (int i = 0; i < stalagtites.size(); i++) {
		if (stalagtites[i].STALAG_ABS_X - camX > 0 && stalagtites[i].STALAG_ABS_X - camX < SCREEN_WIDTH) {
			stalagtX.push_back(stalagtites[i].STALAG_ABS_X - camX);
			stalagtH.push_back(stalagtites[i].STALAG_HEIGHT + WallBlock::block_side);
		}
	}
	for (int i = 0; i < turrets.size(); i++) {
		if (turrets[i].BLOCK_ABS_X - camX > 0 && turrets[i].BLOCK_ABS_X - camX < SCREEN_WIDTH) {
			turretX.push_back(turrets[i].BLOCK_ABS_X - camX);
			turretBottom.push_back(turrets[i].bottom);
			turretH.push_back(turrets[i].BLOCK_HEIGHT + WallBlock::block_side);
		}
	}
	// for (int i = 0; i < kamikazes.size(); i++) {
	// 	if (kamikazes[i].getRelX() > 0 && kamikazes[i].getRelX() < SCREEN_WIDTH && kamikazes[i].getRelY() > 0 && kamikazes[i].getRelY() < SCREEN_HEIGHT) {
	// 		kamiX.push_back(kamikazes[i].getRelX() + kamikazes[i].BLOCK_WIDTH/2);
	// 		kamiY.push_back(kamikazes[i].getRelY() + kamikazes[i].BLOCK_HEIGHT/2);
	// 	}
	// }
	int kamiX = kam->getX();
	int kamiY = kam->getY();
	PathSequence * path = cave_system->getPathSequence();

	int cave_y = -1;				// y coordinate of the center of the cave. -1 if there is no relevant cave
	int abs_enemy_x = en->getX() + en->getWidth() / 2 + camX;
	// Absolute start and end coordinates of the cave
	int startX = cave_system->getStartX();
	int endX = cave_system->getEndX();
	int index = -1;
	if (abs_enemy_x > startX && abs_enemy_x < endX)
	{
		index = (abs_enemy_x - startX) / CaveBlock::CAVE_BLOCK_WIDTH;
		cave_y = path->y[index] * CaveBlock::CAVE_BLOCK_HEIGHT;
	}
	else if (abs_enemy_x < startX && abs_enemy_x + 400 > startX)
	{
		index = 0;
		cave_y = path->y[0] * CaveBlock::CAVE_BLOCK_HEIGHT;
	}
	en->move(playerX, playerY, bulletX, bulletY, bulletVelX, bulletVelY, stalagmX, stalagmH, stalagtX, stalagtH, turretX, turretH, turretBottom, kamiX, kamiY, cave_y);
}

int getScore(){ return (int) (camX / 100); }

void saveHighScore()
{
	std::ofstream highscore_file;
	highscore_file.open("highscore", std::ofstream::out | std::ofstream::trunc);
	highscore_file << std::to_string(getScore());
	highscore_file.close();

}

int readHighScore()
{
	std::ifstream highscore_file("highscore");
	if (highscore_file.is_open())
	{
		std::string highscore_file_line;
		std::getline(highscore_file, highscore_file_line);
		highscore_file.close();
		return std::stoi(highscore_file_line);
	}
	else
	{
		highscore_file.close();
		return 0;
	}
}

void check_missile_collisions()
{
	for (int i = 0; i < missiles.size(); i++)
	{
		missiles[i]->move();

		bool destroyed = false;

		// Check if the missile is out of the screen boundaries
		if (missiles[i]->getY() > FLOOR_BOTTOM)
		{
			destroyed = missiles[i]->ricochet();
		}
		else if (missiles[i]->getY() < ROOF_TOP)
		{
			destroyed = missiles[i]->ricochet();
		}
		else if (blocks->checkCollision(missiles[i]))
		{
			destroyed = true;
		}
		else
		{
			double player_distance = missiles[i]->calculate_distance(player->getPosX(), player->getPosY());
			double enemy_distance = missiles[i]->calculate_distance(en->getX(), en->getY());

			int missile_hitbox = missiles[i]->get_blast_radius() / 3;

			// Explode the warhead if the missile hits the enemy or player
			if (player_distance <= missile_hitbox || enemy_distance <= missile_hitbox)
			{
				// Deal damage to the player and/or enemy depending on their distance and blast radius

				if (player_distance <= missiles[i]->get_blast_radius())
				{
					double damage = missiles[i]->calculate_damage(player->getPosX(), player->getPosY());
					player->hit(damage);
				}

				if (enemy_distance <= missiles[i]->get_blast_radius())
				{
					double damage = missiles[i]->calculate_damage(en->getX(), en->getY());
					en->hit(damage);
				}

				destroyed = true;
			}
		}

		// Remove missiles from the game if they are destroyed
		// after rendering explosion
		if (destroyed)
		{
			blocks->addExplosion(missiles[i]->getX() + camX, missiles[i]->getY() + camY, missiles[i]->getHeight(), missiles[i]->getHeight(), 0);
			delete missiles[i];
			missiles.erase(missiles.begin() + i);
		}
	}
}

int main() {
	if (!init()) {
		std::cout <<  "Failed to initialize!" << std::endl;
		close();
		return 1;
	}

	trash_beat = loadMusic("sounds/lebron_trash_beat.wav");
	song = loadMusic("sounds/track_2.wav");

	srand(time(NULL));


	//Start the player on the left side of the screen
	player = new Player(SCREEN_WIDTH/4 - Player::PLAYER_WIDTH/2, SCREEN_HEIGHT/2 - Player::PLAYER_HEIGHT/2, gRenderer);

	//random open air area
	int openAir = rand() % ((LEVEL_WIDTH-50)/72) + 50;
    int openAirLength = (rand() % 200) + 100;

	cave_system = new CaveSystem();
	blocks = new MapBlocks(LEVEL_WIDTH, LEVEL_HEIGHT, gRenderer, CaveSystem::CAVE_SYSTEM_FREQ, CaveBlock::CAVE_SYSTEM_PIXEL_WIDTH, openAir, openAirLength);
	start_screen= new StartScreen(loadImage("sprites/StartScreen.png"),loadImage("sprites/start_button.png"));
	game_over = new GameOver();



	//start enemy on left side behind player
	en = new Enemy(100, SCREEN_HEIGHT/2, 125, 53, 200, 200, gRenderer);
	kam = new Kamikaze(SCREEN_WIDTH+125, SCREEN_HEIGHT/2, 125, 53, 1000, gRenderer);

	Bullet* newBullet;
	std::string fps;//for onscreen fps
	std::string score; // for onscreen score
	int high_score = readHighScore(); // For onscreen high score
	std::string high_score_string;


	SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Event e;
	bool gameon = true;

	while(start_screen->notStarted){
		while(SDL_PollEvent(&e)) {
			if(e.type==SDL_QUIT){
				start_screen->notStarted=false;
				gameon=false;
			}
			start_screen->handleEvent(e);
		}
		start_screen->render(gRenderer);
		SDL_RenderPresent(gRenderer);
	}

	while(gameon) {

		if (current_track != 0 && !game_over->isGameOver) {
			current_track = 0;
			Mix_PlayMusic(song, -1);
		}
		// Scroll to the side, unless the end of the level has been reached
		time_since_horiz_scroll = SDL_GetTicks() - last_horiz_scroll;
		camX += (double) (SCROLL_SPEED * time_since_horiz_scroll) / 1000;
		if (camX > LEVEL_WIDTH - SCREEN_WIDTH) {
			camX = LEVEL_WIDTH - SCREEN_WIDTH;
		}
		last_horiz_scroll = SDL_GetTicks();

		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {

				int current_highscore = readHighScore();
				if (current_highscore < getScore() || current_highscore == 0)
				{
					saveHighScore();
				}

				gameon = false;
			}
			// Game can end by either pressing on '7' on the numpad or on top row of numbers
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && (e.key.keysym.sym == SDLK_7 || e.key.keysym.sym == SDLK_KP_7))
			{
				game_over->isGameOver = true;
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE) {
				newBullet = player->handleForwardFiring();
				if (newBullet != nullptr) {
					bullets.push_back(newBullet);
				}
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_b) {
				newBullet = player->handleBackwardFiring();
				if (newBullet != nullptr) {
					bullets.push_back(newBullet);
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
		// If the kamikaze is offscreen, create a new one
		if (kam->getX() < -kam->getWidth()) {
			// delete kam;
			// kam = new Kamikaze(SCREEN_WIDTH+125, SCREEN_HEIGHT/2, 125, 53, 5000, gRenderer);
			kam->setX(SCREEN_WIDTH+125);
			kam->setY(SCREEN_HEIGHT/2);
			kam->setArrivalTime(5000);
		}

		// Move player
		player->move(SCREEN_WIDTH, SCREEN_HEIGHT, LEVEL_HEIGHT, camY);

		//move enemy
		moveEnemy(en, kam);
		newBullet = en->handleFiring();
		if (newBullet != nullptr) {
			bullets.push_back(newBullet);
		}
		
		missiles = blocks->handleFiring(missiles, player->getPosX(), player->getPosY());

		kam->move(player, SCREEN_WIDTH);
		//move the bullets
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
		}

		//Move Blocks and check collisions
		blocks->moveBlocks(camX, camY);
		blocks->checkCollision(player);
		blocks->checkCollision(en);

		if (blocks->checkCollision(kam)){
			blocks->addExplosion(kam->getX() + camX, kam->getY() + camY, kam->getWidth(), kam->getHeight(),0);
			kam->setX(SCREEN_WIDTH+125);
			kam->setY(SCREEN_HEIGHT/2);
			kam->setArrivalTime(5000);
		}
		
		//kam->checkCollision(player, gRenderer);
		for (int i = bullets.size() - 1; i >= 0; i--) {
			// If the bullet leaves the screen or hits something, it is destroyed
			bool destroyed = false;
			if(bullets[i]->getY() > FLOOR_BOTTOM){
				destroyed = bullets[i]->ricochetFloor(); // rng chance to ricochet or get destroyed
			}
			else if(bullets[i]->getY() < ROOF_TOP){
				destroyed = bullets[i]->ricochetRoof(); // rng chance to ricochet or get destroyed
			}
			else if (blocks->checkCollision(bullets[i])){
				destroyed = true;
			}
			else if (player->checkCollisionBullet(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getWidth(), bullets[i]->getHeight())) {
				destroyed = true;
				player->hit(5);
			}
			else if (kam->checkCollisionBullet(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getWidth(), bullets[i]->getHeight())) {
				destroyed = true;
				blocks->addExplosion(kam->getX() + camX, kam->getY() + camY, kam->getWidth(), kam->getHeight(),0);
				// delete kam;
				// kam = new Kamikaze(SCREEN_WIDTH+125, SCREEN_HEIGHT/2, 125, 53, 5000, gRenderer);
				kam->setX(SCREEN_WIDTH+125);
				kam->setY(SCREEN_HEIGHT/2);
				kam->setArrivalTime(5000);
			}else if (en->checkCollision(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getWidth(), bullets[i]->getHeight())){
				destroyed = true;
				en->hit(5);
				if (en->getHealth() == 0)
					blocks->addExplosion(en->getX() + camX, en->getY() + camY, en->getWidth(), en->getHeight(),0);
			}
			if (destroyed) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}

		check_missile_collisions();

		// Check collisions between enemy and player
		if (en->checkCollision(player->getPosX(), player->getPosY(), player->getWidth(), player->getHeight())) {
			player->hit(10);
			en->hit(10);
			if (en->getHealth() == 0)
				blocks->addExplosion(en->getX() + camX, en->getY() + camY, en->getWidth(), en->getHeight(),0);
		}

		if((int) camX % CaveSystem::CAVE_SYSTEM_FREQ < ((int) (camX - (double) (SCROLL_SPEED * time_since_horiz_scroll) / 1000)) % CaveSystem::CAVE_SYSTEM_FREQ)
		{
			// std::cout << "Creating Cave System" << std::endl;
			cave_system = new CaveSystem(camX, camY, SCREEN_WIDTH);
		}

		if(cave_system->isEnabled)
		{
			cave_system->moveCaveBlocks(camX, camY);
			cave_system->checkCollision(player);
		}

		// If the player hits the kamikaze, blow up the kamikaze, damage the player, and make a new kamikaze
		if (player->checkCollisionKami(kam->getX(), kam->getY(), kam->getWidth(), kam->getHeight())) {
			blocks->addExplosion(kam->getX() + camX, kam->getY() + camY, kam->getWidth(), kam->getHeight(),0);
			player->hit(10);
			// delete kam;
			// kam = new Kamikaze(SCREEN_WIDTH+125, SCREEN_HEIGHT/2, 125, 53, 5000, gRenderer);
			kam->setX(SCREEN_WIDTH+125);
			kam->setY(SCREEN_HEIGHT/2);
			kam->setArrivalTime(5000);
		}

		if (en->checkCollision(kam->getX(), kam->getY(), kam->getWidth(), kam->getHeight())){
			blocks->addExplosion(kam->getX() + camX, kam->getY()+camY, kam->getWidth(), kam->getHeight(),0);
			en->hit(10);
			// delete kam;
			// kam = new Kamikaze(SCREEN_WIDTH+125, SCREEN_HEIGHT/2, 125, 53, 5000, gRenderer);
			kam->setX(SCREEN_WIDTH+125);
			kam->setY(SCREEN_HEIGHT/2);
			kam->setArrivalTime(5000);
		}

		// Clear the screen
		SDL_RenderClear(gRenderer);

		// Draw the player
		player->render(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		// Draw the enemy
		en->renderEnemy(gRenderer);

		kam->renderKam(SCREEN_WIDTH, gRenderer);

		blocks->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer, cave_system->isEnabled);
		if (cave_system->isEnabled)
			cave_system->render(SCREEN_WIDTH, SCREEN_HEIGHT, gRenderer);

		//draw the bullets
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->renderBullet(gRenderer);
		}

		// Render the missiles
		for (auto& missile : missiles)
		{
			missile->renderMissile(gRenderer);
		}

		framecount++;
		fps_cur_time=SDL_GetTicks();
		if (fps_cur_time - fps_last_time > 1000) {
			fps= std::to_string((int) (framecount / ((fps_cur_time - fps_last_time) / 1000.0)));
			fps +=" fps";
			// reset
			fps_last_time = fps_cur_time;
			framecount = 0;
		}
		Text fps_text(gRenderer, "sprites/comic.ttf", 16, fps, {255,255,255,255});
		fps_text.render(gRenderer,20,20);

		score = "Score: ";
		score.append(std::to_string(getScore()));
		Text score_text(gRenderer, "sprites/comic.ttf", 16, score, {255, 255, 255, 255});
		score_text.render(gRenderer, SCREEN_WIDTH - 130, 7);

		high_score_string = "High Score: ";
		high_score_string.append(std::to_string(high_score));
		Text high_score_text(gRenderer, "sprites/comic.ttf", 16, high_score_string, {255, 255, 255, 255});
		high_score_text.render(gRenderer, SCREEN_WIDTH - 130, 32);

		std::string health_string = "Health ";
		Text healthText(gRenderer, "sprites/comic.ttf", 20, health_string, {255, 255, 255, 255});
		healthText.render(gRenderer, 140, SCREEN_HEIGHT - 52);

		int health = player->getHealth();
		SDL_Rect outline = {199, SCREEN_HEIGHT - 56, 202, 32};
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &outline);
		if (health > 75) {
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		}
		else if (health >= 50) {
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		}
		else if (health >= 20) {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
		}
		else {
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		}
		SDL_Rect health_rect = {200, SCREEN_HEIGHT - 55, 2 * health, 30};
		SDL_RenderFillRect(gRenderer, &health_rect);

		if(health < 1){
			game_over->isGameOver = true;
			int over = game_over->handleEvent(e, player, blocks,gRenderer);
			if(over){
				gameon = false;
				close();
			}
		}
		if(game_over->isGameOver)
		{
			if (current_track != 1) {
				Mix_PlayMusic(trash_beat, -1);
				current_track = 1;
			}
			game_over->stopGame(player, blocks);
			game_over->render(gRenderer);
			camX = 0;
            camY = LEVEL_HEIGHT - SCREEN_HEIGHT;
		}



		SDL_RenderPresent(gRenderer);
	}

	// Out of game loop, clean up
	close();
}
