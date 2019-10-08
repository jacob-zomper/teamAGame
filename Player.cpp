#include <SDL.h>
#include "Player.h"

Player::Player(int xPos, int yPos)
{
    x_pos = xPos;
    y_pos = yPos;
    x_vel = 0;
    y_vel = 0;
}

//Takes key presses and adjusts the player's velocity
void Player::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
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
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
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
void Player::move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY)
{
    if (y_vel > MAX_PLAYER_VEL)
        y_vel = MAX_PLAYER_VEL;
    else if (y_vel < -MAX_PLAYER_VEL)
        y_vel = -MAX_PLAYER_VEL;
    if (x_vel > MAX_PLAYER_VEL)
        x_vel = MAX_PLAYER_VEL;
    else if (x_vel < -MAX_PLAYER_VEL)
        x_vel = -MAX_PLAYER_VEL;

	time_since_move = SDL_GetTicks() - last_move;
    x_pos += (x_vel * time_since_move) / 1000;
    y_pos += (y_vel * time_since_move) / 1000;

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
        camY += (y_vel * time_since_move) / 1000;
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
        camY += (y_vel * time_since_move) / 1000;
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
void Player::render(SDL_Renderer *gRenderer)
{
    //Draw player as cyan rectangle
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_Rect fillRect = {(int) x_pos, (int) y_pos, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderFillRect(gRenderer, &fillRect);
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
void Player::undoXMove() {x_pos -= (x_vel * time_since_move) / 1000;}
void Player::undoYMove() {y_pos -= (y_vel * time_since_move) / 1000;}
void Player::redoXMove() {x_pos += (x_vel * time_since_move) / 1000;}
void Player::redoYMove() {y_pos += (y_vel * time_since_move) / 1000;}
