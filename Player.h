#ifndef Player_H
#define Player_H

#include <SDL.h>

class Player
{
public:
    //The dimensions of the player
    static const int PLAYER_WIDTH = 125;
    static const int PLAYER_HEIGHT = 53;

    //Maximum axis velocity of the player
    static const int MAX_PLAYER_VEL = 300;
	static const int ANIMATION_FREQ = 100;
	
	// Move and animation times, needed for framerate-independent movement and animation speeds
	int time_since_move;
	int last_move;
	
	// Sprites for the player
	SDL_Texture* sprite1;
	SDL_Texture* sprite2;

    //Initializes the variables
    Player(int xPos, int yPos, SDL_Renderer *gRenderer);

    //Takes key presses and adjusts the player's velocity
    void handleEvent(SDL_Event &e);
    //Moves the player
    void move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY);

    //Shows the player on the screen relative to the camera
    void render(SDL_Renderer *gRenderer);
    //Position and velocity accessors
    int getPosX();
    int getPosY();
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