#ifndef bullet_H
#define bullet_H

#include <SDL.h>

class Bullet
{
public:
    Bullet(int x, int y, int vel);

    void renderBullet(SDL_Renderer* gRenderer);

    void move();

    int getX();

    int getY();

    SDL_Rect* getHitbox();

private:
    //define's size of bullet
    const int width;
    const int height;

    // x and y position of bullet
    //y will never be updated
    int xPos;
    int yPos;

    // velocity of bullet
    // y velocity will always be 0
    int xVel;

    SDL_Rect bullet_sprite;
    SDL_Rect hitbox;
};

#endif