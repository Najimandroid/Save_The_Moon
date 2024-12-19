#pragma once
#include "Player.h"
#include "Level.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Wall
{
private:

	bool breakable;
	float health;

	sf::Vector2f textureCoords;
	sf::Sprite* sprite;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::RectangleShape hitbox;

	sf::Color color;
public:

	Wall(sf::Vector2f position_, sf::Vector2f hitboxSize_, bool isBreakable_, float health_) :
		position(position_), breakable(isBreakable_), health(health_), color(sf::Color(155, 155, 155))
	{
		initHitbox(hitboxSize_); velocity = { 0, 0 }; textureCoords = { 0, 0 };
		sprite = nullptr;
	}

	Wall(sf::Vector2f position_, sf::Vector2f hitboxSize_) :
		position(position_), breakable(false), health(1), color(sf::Color(155, 155, 155))
	{ 
		initHitbox(hitboxSize_); velocity = { 0, 0 };
		sprite = nullptr;
	}

	Wall() :
		position({0, 0}), breakable(false), health(1), color(sf::Color(155, 155, 155))
	{ 
		initHitbox({0, 0}); velocity = { 0, 0 };
		sprite = nullptr;
	}

	virtual ~Wall();

	bool isBreakable() { return breakable; }
	bool collided(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize);

	float getHealth() { return health; }

	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getVelocity() { return velocity; }
	sf::Vector2f getTextureCoords() { return textureCoords; }

	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Sprite* getSprite() { if (sprite) { return sprite; } return nullptr; }
	sf::Color getColor() { return color; }

	void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	void setPosition(sf::Vector2f newPosition) { position = newPosition; }

	void setTextureCoords(sf::Vector2f newCoords) { sprite = nullptr; textureCoords = newCoords; }
	void setSprite(sf::Sprite* newSprite) { sprite = newSprite; }

	void initHitbox(sf::Vector2f hitboxSize);
};

class WallManager
{
private:
	static WallManager* instance;

	std::vector <Wall*> walls;
	sf::Texture texture;

	WallManager() { if (!loadTexture()) std::cout << "Walls texture not loaded!"; }
public:
	static WallManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new WallManager();
		}
		return instance;
	}

	Wall* spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize);
	Wall* spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize, bool isBreakable, float health);

	void drawWalls(sf::RenderWindow& window);

	void setSprites();
	bool loadTexture();

	void updatePositions(float deltaTime);

	bool detectCollision(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize);

	sf::Vector2f getWallsVelocity();

	std::vector<Wall*>& getWalls()
	{
		return walls;
	}
};