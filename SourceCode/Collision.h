/*In Collision.h header file Collision class is defined with methods declared
AABB() method is overloaded to detect collisions between different objects
1.Collision between rectangles
2.Collison between ColliderComponents*/
#pragma once
#include <SDL.h>
#include "EntityComponentSystem/Components.h"

class Collision
{
private:
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};