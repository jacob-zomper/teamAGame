#ifndef Player_H
#define Player_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "bullet.h"

class Player
{
public:
	static constexpr double PI = 3.14159265358979323846;

	//The default dimensions of the player
    static const int PLAYER_WIDTH = 125;
    static const int PLAYER_HEIGHT = 53;

    //The dimensions of the player's hurtbox
    int player_hurt_width;
    int player_hurt_height;
    int s_player_hurt_width;
   	int s_player_hurt_height;

    //Maximum axis velocity, animation frequency, and shot frequency of the player
    static const int MAX_PLAYER_VEL = 300;
	static const int MAX_SHOOT_HEAT = 100000;
	static const int SHOOT_COST = 7000;
	static const int RECOVERY_RATE = 10;
	static const int COOLDOWN_TIME = 2000;
	static const int INFINITE_TIME = 4000;
	static const int INVINCE_TIME = 5000;
	static const int AUTOFIRE_TIME = 4000;
	static const int SMALL_TIME = 6000;

	// Animation frequency, the frequency with which the player flickers when hit, and the amount of time the player flickers after being hit
	static const int ANIMATION_FREQ = 100;
	static const int FLICKER_FREQ = 50;
	static const int FLICKER_TIME = 500;

    //The dimensions of the player
    int player_width;
    int player_height;

	// Move and shooting times, needed for framerate-independent movement and animation speeds
	int time_since_move;
	int time_since_f_shot;
	int time_since_b_shot;
	int last_move;
	int fshot_heat;
	int bshot_heat;
	int fshot_max_time;
	int bshot_max_time;
	bool fshot_maxed;
	bool bshot_maxed;
	int time_since_inf;
	int time_since_invincible;
	int time_since_auto;
	int time_since_small;
	bool infiniteShooting;
	bool invincePower;
	bool autoFire;
	bool small;

	// Last time the player was hit, and their current health (out of 100)
	int time_hit;
	int health;
  int barrel_heat;
  int time_since_cool;
  int last_cool;

	double bg_X;
    double tiltAngle;
    bool xp_decel;
    bool xn_decel;
    bool yp_decel;
    bool yn_decel;

	// Sprites for the player
	SDL_Texture* sprite1;
	SDL_Texture* sprite2;
	int difficulty;

	// Sounds
	Mix_Chunk *bullet_shot;
	Mix_Chunk *hit_sound;

	// Used to load sprites
	SDL_Texture* loadImage(std::string fname, SDL_Renderer *gRenderer);
	void initializeSprites(int diff, SDL_Renderer *gRenderer);

    //Initializes the variables
    Player(int xPos, int yPos, int diff, SDL_Renderer *gRenderer);
	~Player();

    //Takes key presses and adjusts the player's velocity
    void handleEvent(SDL_Event &e);
	void handleMute();
    //Moves the player
    void acceleration(bool &increasing, bool &decreasing, float &accel, float &accelerate_by, float &deccelerate_factor, int &vel);
    void move(int SCREEN_WIDTH, int SCREEN_HEIGHT, int LEVEL_HEIGHT, int camY);

    //Shows the player on the screen relative to the camera
    void render(SDL_Renderer *gRenderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);

	// Damages the player when they've been hit
	void hit(int damage);

	//heals player
	void heal(int amount);

	// Handle collisions
	bool checkCollisionKami(int kamiX, int kamiY, int kamiW, int kamiH);
	bool checkCollisionBullet(int bullX, int bullY, int bullW, int bullH);
	bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight);

	// Creates bullets when the player wants to fire forwards or backwards
	Bullet* handleForwardFiring();
	Bullet* handleBackwardFiring();

	//Accessors
    int getPosX();
    int getPosY();
    void setVelX(int vel_x);
    void setVelY(int vel_y);
    int getVelX();
    int getVelY();
    void setPosX(int x);
    void setPosY(int y);
	int getWidth();
	int getHeight();
	int getHitboxX();
	int getHitboxY();
	int getHurtWidth();
	int getHurtHeight();
	int getHealth();
	int getFrontHeat();
	int getBackHeat();
	void setHealthMax();
	void setInfiniteVal(bool);
	void setInvinceVal (bool);
	void setAutoFire(bool);
	void setSmall(bool);
	void resetHeatVals();
	bool getAutoFire();
	bool getSmall();

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
    float x_accel, y_accel;
};

#endif
