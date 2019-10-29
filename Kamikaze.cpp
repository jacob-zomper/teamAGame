
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Kamikaze.h"

SDL_Texture* Kamikaze::loadImage(std::string fname, SDL_Renderer *gRenderer) {
  SDL_Texture* newText = nullptr;

  SDL_Surface* startSurf = IMG_Load(fname.c_str());
  if (startSurf == nullptr) {
    std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
  }

  newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

Kamikaze::Kamikaze(int x, int y, int w, int h, SDL_Renderer* gRenderer) :xPos{(double) x}, yPos{(double) y}, width{w}, height{h}{
  kam_sprite = {(int) xPos, (int) yPos, width, height};
  kam_hitbox = kam_sprite;
  last_move = SDL_GetTicks();
  last_assult = SDL_GetTicks();
  sprite1 = loadImage("sprites/EnemyPlaneK1.png", gRenderer);
  sprite2 = loadImage("sprites/EnemyPlaneK2.png", gRenderer);
  tiltAngle = 0;
  isGone = false;
}

void Kamikaze::renderKam(int SCREEN_WIDTH, SDL_Renderer* gRenderer) {

    if(xPos < SCREEN_WIDTH && !expActive){
      if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1)
        SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &kam_sprite, tiltAngle, nullptr, SDL_FLIP_NONE);
      else
        SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &kam_sprite, tiltAngle, nullptr, SDL_FLIP_NONE);
      kam_hitbox=kam_sprite;
    }

    if(expActive){
      for (int i = 0; i < boom.size(); i++)
        SDL_RenderCopyEx(gRenderer, boom[i].sprite, nullptr, &boom[i].hitbox, 0.0, nullptr, SDL_FLIP_NONE);
      expActive = false;
    }
}

void Kamikaze::move(Player* p, int SCREEN_WIDTH){
  time_since_move = SDL_GetTicks() - last_move;
  time_since_assult = SDL_GetTicks() - last_assult;
  xVelo = 0;
  yVelo = 0;
  tiltAngle = 0;
  if (xPos > SCREEN_WIDTH - width - 10)
    xVelo = -MAX_MOVE_VELO;
  else{
    if (yPos > p->getPosY()+(height/2)){
      tiltAngle = 15;
      yVelo = -MAX_MOVE_VELO;
    }

    if (yPos < p->getPosY()-(height/2)){
      tiltAngle = -15;
      yVelo = MAX_MOVE_VELO;
    }

    if (xPos < p->getPosX()){
      tiltAngle = 0;
      yVelo = 0;
    }
  }
  if (time_since_assult > ASSULT_FREQ && xPos > -width){
      xVelo = -MAX_ASSULT_VELO;
  }

  xPos += (double) (xVelo * time_since_move)/1000;
  yPos += (double) (yVelo * time_since_move)/1000;
  kam_sprite = {(int)xPos,(int)yPos,width,height};
  kam_hitbox = kam_sprite;
  last_move = SDL_GetTicks();


  ///////////////////////////// also added expActive down there
  if(xPos <= -width || expActive){
    last_assult = SDL_GetTicks();
    ////////////
    for (int i = boom.size() - 1; i >= 0; i--)
  	{
  		boom[i].current_size = (double) boom[i].INITIAL_EXPLOSION_SIZE + ((SDL_GetTicks() - boom[i].explosion_time) * boom[i].EXPLOSION_SPEED) / 1000;
  		boom[i].abs_x = boom[i].center_x - boom[i].current_size / 2;
  		boom[i].abs_y = boom[i].center_y - boom[i].current_size / 2;
  		boom[i].rel_x = boom[i].abs_x - xPos;
  		boom[i].rel_y = boom[i].abs_y - yPos;
  		boom[i].hitbox = {(int)boom[i].rel_x, (int)boom[i].rel_y, (int)boom[i].current_size, (int)boom[i].current_size};
  		// If the explosion has reached its maximum size, get rid of it
  		if (boom[i].current_size >= boom[i].FINAL_EXPLOSION_SIZE) {
  			boom.erase(boom.begin() + i);
  		}
  	}
    /////////////////
    isGone = true;
  }
}

bool Kamikaze::checkCol(int x, int y, int w, int h, int tx, int ty, int tw, int th){
  if (x + w < tx || x > tx + tw)
      return false;
  if (y + h < ty || y > ty + th)
      return false;
  return true;
}



void Kamikaze::checkCollision(Player* p, SDL_Renderer* gRenderer){
  for (int i = boom.size() - 1; i >=0; i--){
    if (checkCol(xPos, yPos, width, height, p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT)){
      boom.push_back(Explosion(xPos + width/2, yPos + height/2, gRenderer));
      expActive = true;
    }
  }
}

int Kamikaze::getX(){
  return (int) xPos;
}

int Kamikaze::getY(){
  return (int) yPos;
}

void Kamikaze::setX(int x){
  xPos = x;
  isGone = false;
}

void Kamikaze::setY(int y){
  yPos = y;
  isGone = false;
}

bool Kamikaze::gCheck(){
  return isGone;
}

int Kamikaze::getWidth() {
  return width;
}

int Kamikaze::getHeight() {
  return height;
}

SDL_Rect* Kamikaze::getHitbox(){
  return &kam_hitbox;
}
