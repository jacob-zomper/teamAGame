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
  bool checkCollision(int x, int y, int w, int h);
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
  double getHealthPercentage();
  bool isDamaged();

  void moveLeft();
  void backToCenter(int SCREEN_WIDTH);

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


  //Pattern functions and variables
  static const int NUM_PATTERNS = 3;
  static const int PATTERN_DELAY = 1000;	// Amount of delay between patterns
  int time_since_pattern;		// Time since a pattern finished
  int last_pattern;				// Time when last pattern finished
  int pattern;					// Current pattern number (0 for no pattern)
  int phase;					// Current phase of a pattern (varies by pattern)	
  bool needsFiring;				// True when it's time to fire
  int numFired;					// Number of missiles fired in pattern so far
  
  // Pattern one methods and variables
  void patternOne(int SCREEN_WIDTH);
  std::vector<Missile*> handleFiringMissilePatternOne(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer);
  static const int pattern_one_delay = 2500;
  
  // Pattern two methods and variables
  void patternTwo(int SCREEN_WIDTH);
  std::vector<Missile*> handleFiringMissilePatternTwo(std::vector<Missile*> missiles, int x, int y, SDL_Renderer* gRenderer);
  static const int PATTERN_TWO_FIRING_FREQ = 500;

  void patternThree(int SCREEN_WIDTH);
  std::vector<Missile *> handleFiringMissilePatternThree(std::vector<Missile *> missiles, int x, int y, SDL_Renderer *gRenderer);

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
  int max_health;
  int difficulty;
  
  // Variables relating to being damaged and destroyed
  bool damaged;
  int time_damaged;
  bool tier2;
  bool destroyed;
  int time_destroyed;

};
#endif
