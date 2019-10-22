#ifndef Player_H
#define Player_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "bullet.h"

class Player
{
public:

    //The dimensions of the player
    static const int PLAYER_WIDTH = 125;
    static const int PLAYER_HEIGHT = 53;

    //Maximum axis velocity, animation frequency, and shot frequency of the player
    static const int MAX_PLAYER_VEL = 300;
	static const int ANIMATION_FREQ = 100;
	static const int SHOOT_FREQ = 2000;
	
	// Move and shooting times, needed for framerate-independent movement and animation speeds
	int time_since_move;
	int last_move;
	int time_since_fshot;
	int last_fshot;
	int time_since_bshot;
	int last_bshot;
	
	double bg_X;
    double tiltAngle;
	
	// Sprites for the player
	SDL_Texture* sprite1;
	SDL_Texture* sprite2;
	SDL_Texture* gBackground;
	
	// Used to load sprites
	SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer);

    //Initializes the variables
    Player(int xPos, int yPos, SDL_Renderer *gRenderer);

    //Takes key presses and adjusts the player's velocity
    void handleEvent(SDL_Event &e);
    //Moves the player
    void move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY);

    //Shows the player on the screen relative to the camera
    void render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    
	// Creates bullets when the player wants to fire forwards or backwards
	Bullet* handleForwardFiring();
	Bullet* handleBackwardFiring();
	
	//Position and velocity accessors
    int getPosX();
    int getPosY();
    void setVelX(int vel_x);
    void setVelY(int vel_y);
    int getVelX();
    int getVelY();
    void setPosX(int x);
    void setPosY(int y);
	
	// Methods that can be used to undo the user's moves when dealing with collisions
	void undoXMove();
	void undoYMove();
	void redoXMove();
	void redoYMove();

private:
    //The X and Y offsets of the player (ON SCREEN)
    double x_pos, y_pos;

    //The velocity of the player
    int x_vel, y_vel;
};

#endif