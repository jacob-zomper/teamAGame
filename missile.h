#ifndef missile_H
#define missile_H

#include <SDL.h>
#include <iostream>
#include <cmath>

class Missile
{
    public:
        static const int MISSILE_SIZE = 15;

        Missile(int x, int y, int xvel, int yvel);

        void renderMissile(SDL_Renderer* gRenderer);

        void move();

        // Calculates how far the entity is to this missile
		double calculate_distance(double entity_x, double entity_y);

        // Calculates how much damage the warhead will do to entity
		double calculate_damage(double entity_x, double entity_y);

        int getX();
        int getY();

        int getWidth();
        int getHeight();

        int getXVel();
        int getYVel();

        SDL_Rect* getHitbox();

    private:
        // The following variables are the same as from bullet

        // Size of missile
        const int width, height;

        // Position coordinates
        double xPos, yPos;

        // Velocity
        double velocity_magnitude, xVel, yVel;

        // Velocity direction in radians
        double pitch;

        SDL_Rect missile_sprite;
        SDL_Rect hitbox;

        // Timing
        int time_since_move;
        int last_move;

        // Time the projectile has been in the air
        double air_time;

        // Missile specific variables:

        // Amount of damage the warhead deals at the center of the blast radius
		double damage;

        // Radius where most damage is caused by the warhead
		double blast_radius;
};

#endif