#ifndef Enemy_H
#define Enemy_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "bullet.h"
#include <vector>
using std::vector;
class Enemy
{
    
    public:
	
		SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer);
		
        //Initializes the variables, Constructor
        Enemy(int x, int y, int w, int h, int xvel, int yvel, SDL_Renderer *gRenderer);

        //Shows the enemy 
        void renderEnemy(SDL_Renderer* gRenderer);

        //Moves the enemy
        void move();
        //For testing purposes
        void move(int x, int y);

        //Position, dimensions, and velocity accessors
        int getX();
        int getY();
		int getWidth();
		int getHeight();
        void setyVelo(int y);
        void setxVelo(int x);
		void setPosX(int x);
		void setPosY(int y);
		
		// Methods that can be used to undo the enemy's moves when dealing with collisions
		void undoXMove();
		void undoYMove();
		void redoXMove();
		void redoYMove();
		
        SDL_Rect* getHitbox();
        Bullet* handleFiring();
		
		// Sprites for the enemy
		SDL_Texture* sprite1;
		SDL_Texture* sprite2;
    private:
    
		// Animation and shooting frequencies of the enemy
		static const int ANIMATION_FREQ = 100;
		static const int FIRING_FREQ = 2000;
		
        //Position and size of the enemy sprite on screen
        double xPos;
        double yPos;
        const int width;
        const int height;

        //Velocity of the enemy
		int maxXVelo;
		int maxYVelo;
        int xVelo;
        int yVelo;
        double tiltAngle;

        //defines the enemy asset
        SDL_Rect enemy_sprite;
        //defines the hitbox of the enemy
        SDL_Rect enemy_hitbox;
		
		// Move times, used for handling framerate-independent movement
		int time_since_move;
		int last_move;
		
		// Shooting times, used for handling framerate-independent firing rate
		int time_since_shoot;
		int last_shot;
};

#endif