/*In KeyboardController.h header file KeyboardController class is defined with members
KeyboardController class inherits from base class Component in EntityComponentSystem.h .init() and update() methods override base class methods
KeyboardController handles keyboard events and actions to perform during these events*/
#pragma once
#include "../game.h"
#include "Components.h"
class KeyboardController:public Component
{
private:
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init()	 override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override
	{
		if (!Game::isPlayerDead)
		{
			if (Game::event.type == SDL_KEYDOWN)
			{
				switch (Game::event.key.keysym.sym)
				{
				case SDLK_w:transform->velocity.y = -1;
					transform->velocity.x = 0;
					sprite->play("run");
					break;
				case SDLK_a:transform->velocity.x = -1;
					transform->velocity.y = 0;
					sprite->play("run");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:transform->velocity.x = 1;
					transform->velocity.y = 0;
					sprite->play("run");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_s:transform->velocity.y = 1;
					transform->velocity.x = 0;
					sprite->play("run");
					break;
				default:
					break;
				}
			}
		}
			

		
		
		/*if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:transform->velocity.y = -0;
				break;
			case SDLK_a:transform->velocity.x = -0;
				break;
			case SDLK_d:transform->velocity.x = 0;
				break;
			case SDLK_s:transform->velocity.y = 0;
				break;
			default:
				break;
			}
		}*/
	}
};
