#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer *gRenderer,
		const std::string &font_path,
		 int font_size,
		 const std::string &message_text,
		 const SDL_Color &color)
{
	_text_texture=loadFont(gRenderer, font_path, font_size, message_text, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

void Text::render(SDL_Renderer *gRenderer, int x, int y) const{
	_text_rect.x=x;
	_text_rect.y=y;
	SDL_RenderCopy(gRenderer, _text_texture, nullptr, &_text_rect);
}

 SDL_Texture *Text::loadFont(SDL_Renderer *gRenderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
 	static TTF_Font *font= TTF_OpenFont(font_path.c_str(), font_size);
 	if(!font) {
		printf("TTF_Init: %s\n", TTF_GetError());
 		std::cerr<<"failed to load font\n";
 	}
 	auto text_surface=TTF_RenderText_Solid(font,message_text.c_str(),color);
 	if (!text_surface){
  		// std::cerr<<"failed to create text surface\n";
 	}
 	auto text_texture=SDL_CreateTextureFromSurface(gRenderer, text_surface);
 	if (!text_texture){
  		// std::cerr<<"failed to create text texture\n";
 	}
 	SDL_FreeSurface(text_surface);
 	return text_texture;
 }