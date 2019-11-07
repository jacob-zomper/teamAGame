#include <missile.h>
#include <SDL.h>
#include <iostream>
#include <cmath>

Missile::Missile(int damage, int blast_radius, int x, int y, int xvel, int yvel) :
	damage{ damage }, blast_radius{ blast_radius }, xPos{ x }, yPos{ y },
	xVel { xvel }, yVel{ yvel } 
	{
		width = MISSILE_SIZE;
		height = MISSILE_SIZE / 5;

		missile_sprite = {(int)xPos, (int)yPos, width, height};
		hitbox = missile_sprite;

		velocity_magnitude = sqrt(pow(xVel, 2) + pow(yVel, 2));

		pitch = 0;
		air_time = 0;
		last_move = SDL_GetTicks();
	}

void Missile::renderMissile(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &missile_sprite);
}

void Missile::move()
{
	time_since_move = SDL_GetTicks() - last_move;

	xPos += (double) time_since_move * xVel / 1000;
	yPos += (double) time_since_move * yVel / 1000;
	air_time += time_since_move;

	missile_sprite = {(int) xPos, (int) yPos, width, height};
	hitbox = missile_sprite;
	last_move = SDL_GetTicks();
}

// Calculates how far the entity is to this missile,
// using the basic distance formula for two points in a X and Y plane
double Missile::calculate_distance(double entity_x, double entity_y)
{
	return abs(sqrt(pow(x_position - entity_x, 2) + pow(y_position - entity_y, 2)));
}

// Calculates how much damage the warhead will do to entity,
// depending on the entity's distance to the warhead
double Missile::calculate_damage(double entity_x, double entity_y)
{
	double distance = calculate_distance(entity_x, entity_y);
	return blast_radius / pow(distance, 2) * damage;
}

// Accessor methods

int Missile::getX()
{
	return xPos;
}

int Missile::getY()
{
	return yPos;
}

int Missile::getWidth()
{
	return width;
}

int Missile::getHeight()
{
	return height;
}

int Missile::getXVel()
{
	return xVel;
}

int Missile::getYVel()
{
	return yVel;
}

SDL_Rect* getHitbox()
{
	return hitbox;
}