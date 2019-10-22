#ifndef Kamikaze_H
#define Kamikaze_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Kamikaze
{
  public:
    SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer);

    //Constructor initializing the variables
    Kamikaze(int x, int y, int w, int h, SDL_Renderer *gRenderer);

    //Shows Kamikaze on screen
    void renderKam(int SCREEN_WIDTH, SDL_Renderer* gRenderer);

    //Move the plane into the frame, follows the player along
    //the y axis then assults the player after a certain period
    //of time
    void move(int x, int y, int SCREEN_WIDTH);

    //Position, dimensions, and velocity accessors
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    SDL_Rect* getHitbox();
    SDL_Texture* sprite1;
    SDL_Texture* sprite2;

  private:
    static const int ANIMATION_FREQ = 100;
    static const int ASSULT_FREQ = 8000;
    static const int MAX_MOVE_VELO = 175;
    static const int MAX_ASSULT_VELO = 800;
    double xPos;
    double yPos;
    int xVelo;
    int yVelo;
    const int width;
    const int height;

    double tiltAngle;

    // Move times, used for handling framerate-independent movement
		int time_since_move;
		int last_move;

    int time_since_assult;
    int last_assult;

    SDL_Rect kam_sprite;
    SDL_Rect kam_hitbox;
};

#endif
