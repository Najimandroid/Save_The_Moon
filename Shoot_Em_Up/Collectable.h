#pragma once
#include "Entity.h"
#include "Level.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>

enum CollectableType
{
	COIN, HEART
};

class Collectable
{
private:
	sf::Vector2f position;
	sf::Vector2f textureCoords = { 0, 0 };

	sf::RectangleShape hitbox;
	sf::Sprite* sprite;

	Player* target;

	CollectableType type;

	std::function<void()> effect;
public:
	Collectable();
	Collectable(sf::Vector2f position_, sf::Vector2f textureCoords_, CollectableType type_);
	~Collectable();

	sf::Sprite* getSprite() { if (sprite) { return sprite; } return nullptr; }
	sf::Vector2f getTextureCoords() { return textureCoords; }
	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Vector2f getPosition() { return position; }
	Player* getTarget() { return target; }

	void setEffect(std::function<void()> effect_) { effect = effect_; }
	void setTarget(Player* target_) { target = target_; }
	void setSprite(sf::Sprite* newSprite) { sprite = newSprite; }

	bool collided(Player* entity);
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

	Collectable* spawnCollectable(sf::Vector2f position_, CollectableType type_);

	void drawCollectables(sf::RenderWindow& window);

	void updatePositions(float deltaTime);

	void checkCollisions(Player* entity);
};