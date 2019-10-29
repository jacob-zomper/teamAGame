#ifndef MapBlocks_H
#define MapBlocks_H

#include <SDL.h>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class WallBlock
{
public:
    static const int block_side = 72;
    static const int border = 1;
    WallBlock();
};

class Stalagmite
{
public:
    int STALAG_ABS_Y;
    int STALAG_ABS_X;

    int STALAG_REL_Y;
    int STALAG_REL_X;

    int STALAG_HEIGHT;
    int STALAG_WIDTH;

    Stalagmite();
    Stalagmite(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width);

    SDL_Texture* sprite;
    int stalagShapeNum;
};

class Stalagtite
{
public:
    int STALAG_ABS_Y;
    int STALAG_ABS_X;

    int STALAG_REL_Y;
    int STALAG_REL_X;

    int STALAG_HEIGHT;
    int STALAG_WIDTH;

    Stalagtite();
    Stalagtite(int LEVEL_WIDTH,int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width);

    SDL_Texture* sprite;
    int stalagShapeNum;

    int beenShot;
    int last_move;
    int time_since_move;
    float acceleration;
    int terminalVelocityYValue = 360;
};

class Turret
{
public:
	// Move and shooting times, needed for framerate-independent shooting
	int time_since_move;
	int last_move;
	static const int SHOOT_FREQ = 1000;

    // absolute coordinates of each Turret
    int BLOCK_ABS_X;
    int BLOCK_ABS_Y;

    // coordinates of each Turret relative to camera
    int BLOCK_REL_X;
    int BLOCK_REL_Y;

    int BLOCK_HEIGHT;
    int BLOCK_WIDTH;

    int BLOCK_SPRITE; // Map to which sprite image this Turret will use.

    Turret();
    Turret(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width);

	int getRelX();
	int getRelY();
	int getAbsX();
	int getAbsY();

    //Sprites for turrets
    SDL_Texture* sprite1;
	SDL_Texture* sprite2;

    //defines the turret asset
    SDL_Rect FB_sprite;
    //defines the hitbox of the turret
    SDL_Rect FB_hitbox;

	Bullet * handleFiring(int posX, int posY);
};

class Explosion
{
public:

	// Variables needed to control the size of the explosion and make it disappear at the right time
	static const int INITIAL_EXPLOSION_SIZE = 30;
	static const int FINAL_EXPLOSION_SIZE = 100;
	static const int EXPLOSION_SPEED = 100;
	int explosion_time;
	double current_size;

	// Absolute location of the explosion's center
	int center_x;
	int center_y;

	// Absolute location of the explosion's top left corner
	double abs_x;
	double abs_y;

	// Location relative to the camera
	double rel_x;
	double rel_y;

	Explosion();
	Explosion(int x_loc, int y_loc, SDL_Renderer *gRenderer);

    //Explosion sprite
    SDL_Texture* sprite;

	//defines the explosion
    SDL_Rect hitbox;
};

class MapBlocks
{

public:
    static const int BLOCKS_STARTING_N = 50;
    int BLOCKS_N = 50;

    static const int STALAG_STARTING_N=50;
    int STALAG_N = 50;

    static const int BLOCK_HEIGHT = 100;
    static const int BLOCK_WIDTH = 100;

	SDL_Renderer *gRenderer;

    std::vector<Turret> blocks_arr;
    std::vector<Stalagmite> stalagm_arr;
    std::vector<Stalagtite> stalagt_arr;
    std::vector<Explosion> explosion_arr;

    MapBlocks();
    MapBlocks(int LEVEL_WIDTH, int LEVEL_HEIGHT, SDL_Renderer *gRenderer, int cave_freq, int cave_width);
    bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight);

    void moveBlocks(int camX, int camY);
	void checkCollision(Player *p);
	void checkCollision(Enemy *e);
	bool checkCollision(Bullet *b);
	std::vector<Bullet*> handleFiring(std::vector<Bullet*> bullets, int posX, int posY);

    void render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer);

private:
    //Animation frequency
    static const int ANIMATION_FREQ = 100;
};

#endif
