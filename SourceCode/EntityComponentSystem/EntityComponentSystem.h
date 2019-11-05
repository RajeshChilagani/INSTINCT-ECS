/*EntityComponentSystem.h implememts a EntityComponentSystem which is an architectural pattern
In ECS we have 3 classes
1.Component class
2.Entity class
2.Manager class
Manager class handles entities like adding entities,updating and drawing them
Entity class adds components to entities.It aslo updates,draws and gets components
Component class is a base class and Specifc component classes inherit from this base class and override the methods in it*/
#pragma once
#include<iostream>
#include<vector>
#include<array>
#include<memory>
#include<bitset>
#include<algorithm>
using namespace std;
class Component;
class Entity;

using ComponentID = size_t;
inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}
template<typename T>
inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}
constexpr size_t maxComponents = 32;
using ComponentBitset = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component
{
private:
public:
	Entity* entity;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual ~Component() {}

};
class Entity
{
private:
	bool active = true;
	vector<unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitset componentBitset;
public:
	void update()
	{
		for (auto& a : components)
		{
			a->update();
		}
		
	}
	void draw() 
	{
		for (auto& a : components)
		{
			a->draw();
		}
	}
	bool isActive() const
	{
		return active;
	}
	void destroy()
	{
		active = false;
	}
	template<typename T>
	bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}
	template <typename T, typename...Targs>
	T& addComponent(Targs&&... mArgs)
	{
		T* c(new T(forward<Targs>(mArgs)...));
		c->entity = this;
		unique_ptr<Component> uPtr{ c };
		components.emplace_back(move(uPtr));
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
		c->init();
		return *c;
	}
	template<typename T>
	T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};
class Manager
{
private:
	vector<unique_ptr<Entity>> entities;
public:
	void update()
	{
		for (auto& e : entities)
		{
			e->update();

		}
		

	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}
	void refresh()
	{
		entities.erase(remove_if(begin(entities), end(entities),
			[](const unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			end(entities));
	}
	Entity& addEntity()
	{
		Entity *e(new Entity());
		unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(move(uPtr));
		return *e;
	}

};