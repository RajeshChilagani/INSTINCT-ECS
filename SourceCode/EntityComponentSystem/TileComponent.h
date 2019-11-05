/*In TileComponent.h header file TileComponent class is defined with constructors and members
TileComponent class inherits from base class Component in EntityComponentSystem.h.init() method overrides base class method
Tiles are created using this component.All boundaries are created using TileComponent in this game*/
#pragma once
#include "Components.h"
#include <SDL.h>
class TileComponent:public Component
{
private:
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect	tileRect;
	int tileId;
	const char* path;

	TileComponent() = default;
	TileComponent(int x,int y,int w,int h,int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileId = id;

		switch (tileId)
		{

		case 0:
			path = "assets/texture1.png";
			break;
		case 1:
			path = "assets/texture2.png";
			break;
		case 2:
			path = "assets/texture3.png";
			break;
		default:
			break;
		}

	}
	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, 1,tileRect.w, tileRect.h);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};