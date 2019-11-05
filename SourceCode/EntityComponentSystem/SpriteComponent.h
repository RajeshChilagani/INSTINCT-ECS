/*In SpriteComponent.h header file SpriteComponent class is defined with constructors and members
SpriteComponent class inherits from base class Component in EntityComponentSystem.h.init(),update()and draw() methods override base class methods
Using SpriteComponent textures are added and drawn for entities */
#pragma once
#include "Components.h"
#include "SDL.h"
#include  "../TextureManager.h"
#include "Animation.h"
#include <map>
class SpriteComponent:public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;
public:
	int animIndex = 0;
	std::map<const char*, Animation> animations;
	SDL_RendererFlip spriteFlip=SDL_FLIP_NONE;
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}
	SpriteComponent(const char* path,bool isAnimated)
	{
		animated = isAnimated;
		Animation idle = Animation(0,10,100);
		Animation run = Animation(1,8,100);
		Animation dead = Animation(2,10,100);

		animations.emplace("idle", idle);
		animations.emplace("run",run);
		animations.emplace("dead",dead);
		play("idle");
		setTexture(path);
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}
	void setTexture(const char* path)
	{
		texture= TextureManager::loadTexture(path);
	}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
		srcRect.y = animIndex * transform->height;
		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);
		desRect.w = transform->width*transform->scale;
		desRect.h = transform->height*transform->scale;


	}
	void draw() override
	{
		TextureManager::draw(texture, srcRect, desRect, spriteFlip);
	}
	void play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}
};
