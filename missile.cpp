#include <missile.h>
#include <SDL.h>
#include <iostream>
#include <cmath>

Missile::Missile(int damage, int blast_radius, int x, int y, int xvel, int yvel) :
	damage{ damage }, blast_radius{ blast_radius }, xPos{ x }, yPos{ y },
	xVel { xvel }, yVel{ yvel } {}

void Missile::renderMissile(SDL_Renderer* gRenderer)
{

}

void Missile::move()
{

}

double Missile::calculate_distance(double entity_x, double entity_y)
{

}

double Missile::calculate_damage(double entity_x, double entity_y)
{

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