#pragma once

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Enemy
{
private:

	float health;
	float damage;

	float speed;

	sf::Vector2f position;
	sf::Vector2f velocity;

public:
	Enemy(float health_, float damage_, sf::Vector2f position_, float speed_);

	sf::Vector2f getPosition() const
	{
		return position;
	}

	float getHealth() const
	{
		return health;
	}

	void setPosition(sf::Vector2f newPosition)
	{
		position = newPosition;
	}

	float getSpeed() const
	{
		return speed;
	}

	void init(float health_, float damage_, sf::Vector2f position_, float speed_);
	void updatePosition(float deltaTime);
};



class EnemyManager
{
private:
	static EnemyManager* instance;

	std::vector <Enemy*> enemies;

	EnemyManager() {}
public:
	static EnemyManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new EnemyManager();
		}
		return instance;
	}

	std::vector <Enemy*> getEnemies()
	{
		return enemies;
	}

	Enemy* spawnEnemy(float health_, float damage_, sf::Vector2f position_, float speed_);

	void drawEnemies(sf::RenderWindow& window);
	void updatePositions(float deltaTime);
};