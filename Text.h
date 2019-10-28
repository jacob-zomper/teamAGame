#ifndef Text_H
#define Text_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Text{
public:
	Text(SDL_Renderer *gRenderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

	void render(SDL_Renderer *gRenderer, int x, int y) const;

	static SDL_Texture *loadFont(SDL_Renderer *gRenderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);


private:
	SDL_Texture *_text_texture= nullptr;
	mutable SDL_Rect _text_rect;
};
#endif