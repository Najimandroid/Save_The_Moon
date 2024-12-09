#pragma once
#include "Entity.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);

	void updatePosition(float deltaTime) override;
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
	void updateStates();

	void update(float deltaTime);
};