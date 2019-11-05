/*In TransformComponent.h header file TransformComponent class is defined with constructors and members
TransformComponent class inherits from base class Component in EntityComponentSystem.h.init() and update() methods override base class methods
position,velocity and scale of entities are managed using this component*/
#pragma once
#include "Components.h"
#include "../Vector2D.h"
class TransformComponent :public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;
	TransformComponent()
	{
		position.zero();
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
	TransformComponent(int s)
	{
		scale = s;
		position.zero();
	}
	TransformComponent(float x, float y, int s, int w, int h)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}
	void init() override
	{
		velocity.zero();
	}
	void update() override
	{
		position.x += velocity.x*speed;
		position.y += velocity.y*speed;
	}
};