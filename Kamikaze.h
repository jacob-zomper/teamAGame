#ifndef Kamikaze_H
#define Kamikaze_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "MapBlocks.h"

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
    void move(Player* p, int SCREEN_WIDTH);
    void checkCollision(Player *p, SDL_Renderer* gRenderer);

    //Position, dimensions, and velocity accessors
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    bool gCheck();
    int getWidth();
    int getHeight();
    bool checkCol(int x, int y, int w, int h, int tx, int ty, int tw, int th);

    SDL_Rect* getHitbox();
    SDL_Texture* sprite1;
    SDL_Texture* sprite2;

  private:
    static const int ANIMATION_FREQ = 100;
    static const int ASSULT_FREQ = 4000;
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

    //Times for between assults of the player
    int time_since_assult;
    int last_assult;

    //bool identifying if the kamikaze is gone
    bool isGone;

    //Explosion when hit something
    std::vector<Explosion> boom;
    bool expActive;

    SDL_Rect kam_sprite;
    SDL_Rect kam_hitbox;


};

#endif
