/*In ColliderComponent.h header file ColliderComponent class is defined with constructors and members
ColliderComponent class inherits from base class Component in EntityComponentSystem.h .init() and update() methods override base class methods
Using ColliderComponents collisions are detected in game.ColliderComponent uses entity's transformComponent for scale and position*/
#pragma once
#include "Components.h"
#include "SDL.h"							
#include <string>
using namespace std;
class ColliderComponent:public Component
{
private:
public :
	SDL_Rect collider;
	string tag;
	TransformComponent* transform;

	ColliderComponent(string tagName)
	{
		tag = tagName;
	}
	~ColliderComponent()
	{

	}
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		Game::colliders.push_back(this);
	}
	void update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.h = transform->height*transform->scale;
		collider.w = transform->width*transform->scale;
	}


};
