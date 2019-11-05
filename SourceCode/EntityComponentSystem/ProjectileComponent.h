/*In ProjectileComponent.h header file ProjectileComponent class is defined with constructors and members
ProjectileComponent class inherits from base class Component in EntityComponentSystem.h.init() and update() methods override base class methods
ProjectileComponent is added to entities to make them projectiles*/
#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include <string>

class ProjectileComponent :public Component
{
private: 
	int range;
	int speed;
	int distance;
	Vector2D velocity;
	TransformComponent* transform;
public :
	string tagName;
	ProjectileComponent(int rng,int spd,Vector2D vel):range(rng),speed(spd),velocity(vel)
	{}
	~ProjectileComponent()
	{}
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}
	void update() override
	{
		distance += speed;
		if (distance > range)
		{
			entity->destroy();
		}
	}

};