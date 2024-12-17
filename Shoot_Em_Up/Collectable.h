#pragma once
#include "Entity.h"
#include "Level.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>

class Collectable
{
private:
	sf::Vector2f position;
	sf::Vector2f textureCoords = { 0, 0 };

	sf::RectangleShape hitbox;

	Entity* target;

	std::function<void()> effect;
public:
	Collectable();
	Collectable(sf::Vector2f position_, void(*effect_)());

	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Vector2f getPosition() { return position; }
	Entity* getTarget() { return target; }

	bool collided(Entity* entity);
	void collected();
	void updatePosition(float deltaTime);
};

class CollectableManager
{
private:
	static CollectableManager* instance;

	sf::Texture texure;
	std::vector<Collectable*> collectables;

	CollectableManager() {}

public:
	static CollectableManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new CollectableManager();
		}
		return instance;
	}

	Collectable* spawnCollectable(sf::Vector2f position_);

	void drawCollectables(sf::RenderWindow& window);

	void updatePositions(float deltaTime);

	void checkCollisions(Entity* entity);
};