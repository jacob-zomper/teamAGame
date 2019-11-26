#ifndef Boss_H
#define Boss_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "missile.h"
#include "bullet.h"

class Boss
{
public:
  SDL_Texture* loadImage(std::string fname, SDL_Renderer* gRenderer);
  Boss(int x, int y, int xvel, int yvel, int diff, SDL_Renderer* gRenderer);
  ~Boss();
  void renderBoss(int SCREEN_WIDTH, SDL_Renderer* gRenderer);
  bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight);
  bool checkCollisionBullet(int x, int y, int w, int h);
  void move(int SCREEN_WIDTH);
  std::vector<Missile*> handleFiringMissile(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer);
  Missile* MissleLoc(int x, int y);
  Bullet* handleFiringUp();
  Bullet* handleFiringDown();
  void hit(int d);

  // Boss width and height
  static const int WIDTH = 250;
  static const int HEIGHT = 106;

  int getX();
  int getY();
  int getWidth();
  int getHeight();
  int getHealth();

  void moveLeft();

  SDL_Texture* sprite1;

private:
  //Boss sprite and hitboxes
  SDL_Rect boss_sprite;
  SDL_Rect boss_hitbox_top;
  SDL_Rect boss_hitbox_bottom;

  //Boss x and y positions
  double xPos;
  double yPos;

  //Boss velocity and movement variables
  static const int MAX_DOWN = 500;
  static const int MAX_UP = 90;
  int maxXVelo;
  int maxYVelo;
  int xVelo;
  int yVelo;
  int time_since_move;
  int last_move;


  //Patern One function and variables
  void patternOne(int SCREEN_WIDTH);
  static const int PATTERNONEFREQ = 1000;
  int time_since_pattern;
  int last_pattern;
  int corner_delay = 2500;
  bool upright;
  bool upleft;
  bool downleft;
  bool downright;
  bool ur_fire;
  bool ul_fire;
  bool dl_fire;
  bool dr_fire;
  bool oneActive;
  int corner_location;

  //Shooting variables
  static const int FIRING_FREQ = 2000;
  int time_since_shot_missile;
  int time_since_shot_up;
  int time_since_shot_down;
  int last_shot_missile;
  int last_shot_up;
  int last_shot_down;

  //Health variables
  int health;

};
#endif
