#ifndef bullet_H
#define bullet_H

#include <SDL.h>

class Bullet
{
public:
	
	static const int BULLET_SIZE = 5;
	
    Bullet(int x, int y, int vel);

    void renderBullet(SDL_Renderer* gRenderer);

    void move();

    int getX();

    int getY();
	
	int getWidth();
	
	int getHeight();
	
	int getXVel();

    SDL_Rect* getHitbox();

private:
    //define's size of bullet
    const int width;
    const int height;

    // x and y position of bullet
    //y will never be updated
    double xPos;
    double yPos;

    // velocity of bullet
    // y velocity will always be 0
    int xVel;

    SDL_Rect bullet_sprite;
    SDL_Rect hitbox;

    //timing variables
    int time_since_move;
    int last_move;

};

#endif