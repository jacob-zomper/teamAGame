#include "bullet.h"
#include "time.h"

// Increase value to have bullets drop slower
// Decrease to have bullets drop faster
const int adjuster = 10;

Bullet::Bullet(int x, int y, int vel) :xPos{(double)x}, yPos{(double)y}, width{BULLET_SIZE}, height{BULLET_SIZE}{
	bullet_sprite = {(int)xPos,(int)yPos,width, height};
	hitbox = bullet_sprite;
	velocity_magnitude = vel;
	xVel = vel;
	pitch = 0;
	air_time = 0;
	last_move = SDL_GetTicks();
};

Bullet::Bullet(int x, int y, int xvel, int yvel) :xPos{(double)x}, yPos{(double)y}, width{BULLET_SIZE}, height{BULLET_SIZE}{
	bullet_sprite = {(int)xPos,(int)yPos,width, height};
	hitbox = bullet_sprite;
	velocity_magnitude = sqrt(xvel * xvel + yvel * yvel);
	xVel = xvel;
	yVel = yvel;
	// Compute pitch
	pitch = atan((double) yvel / xvel);
	if (xvel < 0)
		pitch = pitch + 3.1415926535;
	
	air_time = 0;
	last_move = SDL_GetTicks();
    	srand(time(NULL));
};

Bullet::~Bullet(){
	delete width;
    delete height;
    delete xPos;
    delete yPos;
    delete velocity_magnitude;
    delete xVel;
    delete yVel;
	delete yVel0;
	delete bullet_sprite;
    delete hitbox;
    delete time_since_move;
    delete last_move;
    delete pitch;
    delete air_time;
}

void Bullet::renderBullet(SDL_Renderer* gRenderer){
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &bullet_sprite);
}

bool Bullet::ricochetFloor(){
	if(((rand() % 100) + (yVel/20)) > 80){ // about 20-40% chance of destruction, higher Velocity = less likely to ricochet
		return true; // destroyed
	}
	yPos = FLOOR_BOTTOM - 3;
	yVel /= -1.5;
	
	return false; // ricocheted
}

bool Bullet::ricochetRoof(){
	if(((rand() % 100) + (yVel/20)) > 80){ // about 20-40% chance of destruction, higher Velocity = less likely to ricochet
		return true; // destroyed
	}
	yPos = ROOF_TOP + 3;
	yVel /= -1.5;
	
	return false; // ricocheted
}

void Bullet::move(){
	time_since_move = SDL_GetTicks() - last_move;

	xVel = adjusted_x_velocity();
	yVel = adjusted_y_velocity();

	xPos += ((double) time_since_move * xVel) / 1000;
	yPos += ((double) time_since_move * yVel) / 1000;
	air_time += time_since_move;

	bullet_sprite ={(int)xPos,(int)yPos,width,height};
	hitbox = bullet_sprite;
	last_move = SDL_GetTicks();
}

int Bullet::adjusted_x_velocity()
{
	// Decrease x velocity to simulate air resistance,
	// but half as slowly as the decrease in y velocity
	int adjustment = air_time * (1/2 / adjuster);
	int x_velocity = velocity_magnitude * cos(pitch);

	// Prevent projectile from changing direction in the x-direction
	int adjusted_x_velocity = x_velocity - adjustment;
	if ((adjusted_x_velocity <= 0 && x_velocity >= 0) || (adjusted_x_velocity >= 0 && x_velocity <= 0))
	{
		adjusted_x_velocity = 0;
	}

	return adjusted_x_velocity;
}

int Bullet::adjusted_y_velocity()
{
	// Decreases the y velocity by the air time to simulate bullet drop
	int y_velocity = velocity_magnitude * sin(pitch) - 15;
	return y_velocity + (air_time / adjuster);
}

int Bullet::getX(){
	return xPos;
}

int Bullet::getY(){
	return yPos;
}

int Bullet::getWidth(){
	return width;
}

int Bullet::getHeight(){
	return height;
}

int Bullet::getXVel() {
	return xVel;
}

int Bullet::getYVel() {
	return yVel;
}

SDL_Rect* Bullet::getHitbox(){
	return &hitbox;
}
