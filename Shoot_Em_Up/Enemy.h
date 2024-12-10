#pragma once
#include "Entity.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

enum EnemyType
{
	DEFAULT, TANK, SWARM
};

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);
	Enemy() {};

	void updatePosition(float deltaTime) override;
};

class Tank : public Enemy
{
public:
	Tank(sf::Vector2f position_)
	{
		position = position_;
		color = sf::Color::Yellow;

		initHitbox({ 75, 75 });
		initProperties(300, 50, 1.5f, true, 5.f);
	}
};

class Swarm : public Enemy
{
public:
	Swarm(sf::Vector2f position_)
	{
		position = position_;
		color = sf::Color::Cyan;

		initHitbox({ 25, 25 });
		initProperties(10, 0, 6.f, false, 0.f);
	}
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

	Enemy* spawnEnemy(sf::Vector2f position_, float health_, float damage_, float speed_);
	Enemy* spawnEnemy(sf::Vector2f position, EnemyType enemyType);

	void drawEnemies(sf::RenderWindow& window);
	void updatePositions(float deltaTime);
	void updateStates();

	void update(float deltaTime);
};