/*In TextureManager.h header file TextureManager class is defined with methods declared to load and draw textures*/
#pragma once
#include "game.h"
class TextureManager
{
public:
	static SDL_Texture* loadTexture(const char* filePath);
	static void draw(SDL_Texture* texture,SDL_Rect srcRect,SDL_Rect desRect,SDL_RendererFlip flip);
	static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect desRect);
};