#ifndef bullet_H
#define bullet_H

#include <SDL.h>
#include <iostream>
#include <cmath>

class Bullet
{
public:

	static const int BULLET_SIZE = 5;
	static const int FLOOR_BOTTOM = 720-79;
    static const int ROOF_TOP = 73;

    Bullet(int x, int y, int vel);
	Bullet(int x, int y, int xvel, int yvel);

    void renderBullet(SDL_Renderer* gRenderer);

    bool ricochetFloor();

    bool ricochetRoof();

    void move();

    int getX();

    int getY();

	int getWidth();

	int getHeight();

	int getXVel();

    int getYVel();

    int adjusted_x_velocity();

    int adjusted_y_velocity();

    SDL_Rect* getHitbox();

private:
    //define's size of bullet
    const int width;
    const int height;

    // x and y position of bullet
    double xPos;
    double yPos;

    // velocity of bullet
    int velocity_magnitude;
    int xVel;
    int yVel;
	int yVel0;

    SDL_Rect bullet_sprite;
    SDL_Rect hitbox;

    //timing variables
    int time_since_move;
    int last_move;

    // Pitch of the bullet in radians
    double pitch;

    // Time the projectile has been in the air
    // Used to calculate air resistance and bullet drop
    double air_time;

};

#endif
