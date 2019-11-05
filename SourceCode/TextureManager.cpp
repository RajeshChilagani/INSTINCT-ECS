/*In TextureManager.cpp,methods declared in TextureManager class are defined
draw() method is overloaded */
#include "TextureManager.h"
SDL_Texture* TextureManager::loadTexture(const char* textureFilePath)
{
	SDL_Surface* tmpSurface = IMG_Load(textureFilePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return tex;
}
void TextureManager::draw(SDL_Texture* texture,SDL_Rect srcRect,SDL_Rect desRect,SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer,texture,&srcRect,&desRect,NULL,NULL,flip);
}
void TextureManager::draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect desRect)
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &desRect);
}