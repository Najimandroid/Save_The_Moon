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
	sf::Sprite* sprite;

	Entity* target;

	std::function<void()> effect;
public:
	Collectable();
	Collectable(sf::Vector2f position_, void(*effect_)());
	~Collectable();

	sf::Sprite* getSprite() { if (sprite) { return sprite; } return nullptr; }
	sf::Vector2f getTextureCoords() { return textureCoords; }
	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Vector2f getPosition() { return position; }
	Entity* getTarget() { return target; }

	void setSprite(sf::Sprite* newSprite) { sprite = newSprite; }

	bool collided(Entity* entity);
	void collected();
	void updatePosition(float deltaTime);
};

class CollectableManager
{
private:
	static CollectableManager* instance;

	sf::Texture texture;
	std::vector<Collectable*> collectables;

	CollectableManager() { if (!loadTexture()) std::cout << "Collectables texture not loaded!"; }

public:
	static CollectableManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new CollectableManager();
		}
		return instance;
	}

	bool loadTexture();
	void setSprites();

	Collectable* spawnCollectable(sf::Vector2f position_);

	void drawCollectables(sf::RenderWindow& window);

	void updatePositions(float deltaTime);

	void checkCollisions(Entity* entity);
};