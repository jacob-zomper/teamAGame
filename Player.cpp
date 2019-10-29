#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"

SDL_Texture* Player::loadImage(std::string fname, SDL_Renderer *gRenderer) {
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

Player::Player(int xPos, int yPos, SDL_Renderer *gRenderer)
{
    x_pos = xPos;
    y_pos = yPos;
    x_vel = 0;
    y_vel = 0;
    x_accel = 0;
    y_accel = 0;
	sprite1 = loadImage("sprites/PlayerPlane1.png", gRenderer);
	sprite2 = loadImage("sprites/PlayerPlane3.png", gRenderer);
	gBackground = loadImage("sprites/cave.png", gRenderer);
    bg_X = 0;
    tiltAngle = 0;
	last_move = SDL_GetTicks();
    xp_decel = true;
    xn_decel = true;
    yp_decel = true;
    yn_decel = true;
	last_fshot = SDL_GetTicks() - SHOOT_FREQ;
	last_bshot = SDL_GetTicks() - SHOOT_FREQ;
}

//Takes key presses and adjusts the player's velocity
void Player::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            yn_decel = false;
            break;

        case SDLK_a:
            xn_decel = false;
            break;

        case SDLK_s:
            yp_decel = false;
            break;

        case SDLK_d:
            x_vel += MAX_PLAYER_VEL;
            xp_decel = false;
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            yn_decel = true;
            break;

        case SDLK_a:
            xn_decel = true;
            break;

        case SDLK_s:
            yp_decel = true;
            break;

        case SDLK_d:
            xp_decel = true;
            break;
        }
    }
}

//Moves the player
void Player::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY)
{
    float to_accel = 0.003*time_since_move;
    float decelFactor = 1.0;
    if(!yn_decel) y_accel -= to_accel;
    if(!yp_decel) y_accel += to_accel;
    if(yn_decel && yp_decel){
        if(y_vel < 0) y_accel += decelFactor*to_accel;
        else if(y_vel > 0) y_accel -= decelFactor*to_accel;
        float to_vel = y_accel*time_since_move;
        y_vel += to_vel;
        if(y_vel != 0 && y_vel <= abs(decelFactor*to_vel) && y_vel >= -abs(decelFactor*to_vel)){
            y_accel = 0;
            y_vel = 0;
        }
    } else{
        float to_vel = y_accel*time_since_move;
        y_vel += to_vel;
    }
    if(y_accel > 3) y_accel = 3;
    else if(y_accel < -3) y_accel = -3;
    
    tiltAngle = 180 * sin(y_accel / 12);

    to_accel /= 2;
    if(!xn_decel) x_accel -= to_accel;
    if(!xp_decel) x_accel += to_accel;
    if(xn_decel && xp_decel){
        if(x_vel < 0) x_accel += decelFactor*to_accel;
        else if(x_vel > 0) x_accel -= decelFactor*to_accel;
        float to_vel = x_accel*time_since_move;
        x_vel += to_vel;
        if(x_vel != 0 && x_vel <= abs(decelFactor*to_vel) && x_vel >= -abs(decelFactor*to_vel)){
            x_accel = 0;
            x_vel = 0;
        }
    } else{
        float to_vel = x_accel*time_since_move;
        x_vel += to_vel;
    }
    if(x_accel > 3) x_accel = 3;
    else if(x_accel < -3) x_accel = -3;


    if (y_vel > MAX_PLAYER_VEL)
        y_vel = MAX_PLAYER_VEL;
    else if (y_vel < -MAX_PLAYER_VEL)
        y_vel = -MAX_PLAYER_VEL;
    if (x_vel > MAX_PLAYER_VEL)
        x_vel = MAX_PLAYER_VEL;
    else if (x_vel < -MAX_PLAYER_VEL)
        x_vel = -MAX_PLAYER_VEL;

	time_since_move = SDL_GetTicks() - last_move;
    x_pos += (double) (x_vel * time_since_move) / 1000;
    y_pos += (double) (y_vel * time_since_move) / 1000;
    bg_X += (double) (time_since_move) / 10;

    // Move the player horizontally
    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos > SCREEN_WIDTH - PLAYER_WIDTH)
    {
        x_pos = SCREEN_WIDTH - PLAYER_WIDTH;
    }

    // Move the player vertically.
    // If they are near the top of the screen, scroll up
    if (y_pos < SCREEN_HEIGHT / 10 && camY > 0)
    {
        y_pos = SCREEN_HEIGHT / 10;
        camY += (double) (y_vel * time_since_move) / 1000;
    }
    // Stop the player if they hit the top of the level
    else if (y_pos < 0)
    {
        y_pos = 0;
    }
    // If they are near the bottom of the screen, scroll down
    else if (y_pos > (9 * SCREEN_HEIGHT) / 10 - PLAYER_HEIGHT && camY < LEVEL_HEIGHT - SCREEN_HEIGHT)
    {
        y_pos = (9 * SCREEN_HEIGHT) / 10 - PLAYER_HEIGHT;
        camY += (double) (y_vel * time_since_move) / 1000;
    }
    // Stop the player if they hit the bottom
    else if (y_pos > SCREEN_HEIGHT - PLAYER_HEIGHT)
    {
        y_pos = SCREEN_HEIGHT - PLAYER_HEIGHT;
    }

    if (camY < 0)
    {
        camY = 0;
    }
    else if (camY > LEVEL_HEIGHT - SCREEN_HEIGHT)
    {
        camY = LEVEL_HEIGHT - SCREEN_HEIGHT;
    }
	last_move = SDL_GetTicks();
}

//Shows the player on the screen relative to the camera
void Player::render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	SDL_Rect bgRect = {-((int)bg_X % SCREEN_WIDTH), 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);
    bgRect.x += SCREEN_WIDTH;
    SDL_RenderCopy(gRenderer, gBackground, nullptr, &bgRect);
    
    SDL_Rect playerLocation = {(int) x_pos, (int) y_pos, PLAYER_WIDTH, PLAYER_HEIGHT};
	// Alternates through the two sprites every ANIMATION_FREQ ticks
    if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
		SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	}
	else {
		SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &playerLocation, tiltAngle, nullptr, SDL_FLIP_NONE);
	}
}

Bullet* Player::handleForwardFiring()
{
	time_since_fshot = SDL_GetTicks() - last_fshot;
	if (time_since_fshot > SHOOT_FREQ) {
		Bullet* b = new Bullet(x_pos+PLAYER_WIDTH+5,y_pos+PLAYER_HEIGHT/2,450);
		last_fshot = SDL_GetTicks();
		return b;
	}
	return nullptr;
}

Bullet* Player::handleBackwardFiring()
{
	time_since_bshot = SDL_GetTicks() - last_bshot;
	if (time_since_bshot > SHOOT_FREQ) {
		Bullet* b = new Bullet(x_pos,y_pos+PLAYER_HEIGHT/2,-450);
		last_bshot = SDL_GetTicks();
		return b;
	}
	return nullptr;
}

//Position and velocity accessors
int Player::getPosX() { return x_pos; };
int Player::getPosY() { return y_pos; };
void Player::setVelX(int vel_x) { x_vel = vel_x; };
void Player::setVelY(int vel_y) { y_vel = vel_y; };
int Player::getVelX() { return x_vel; };
int Player::getVelY() { return y_vel; };
void Player::setPosX(int x) { x_pos = x; }
void Player::setPosY(int y) { y_pos = y; }

// Methods that can be used to undo the user's moves when dealing with collisions
void Player::undoXMove() {x_pos -= (double) (x_vel * time_since_move) / 1000;}
void Player::undoYMove() {y_pos -= (double) (y_vel * time_since_move) / 1000;}
void Player::redoXMove() {x_pos += (double) (x_vel * time_since_move) / 1000;}
void Player::redoYMove() {y_pos += (double) (y_vel * time_since_move) / 1000;}
