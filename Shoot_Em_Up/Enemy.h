#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Level.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

enum EnemyType
{
	DEFAULT, TANK, SWARM, WAVE, WHEEL
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

		initHitbox({ WindowConfig::getInstance()->SIZE_Y / 27.f, WindowConfig::getInstance()->SIZE_Y / 27.f });
		initProperties(300, 50, 1.5f, true, 5.f);
	}
};

class Wave : public Enemy
{
public:
	Wave(sf::Vector2f position_)
	{
		position = position_;
		color = sf::Color::Red;

		initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
		initProperties(100, 25, 2.f, true, .5f);
	}

	void updatePosition(float deltaTime) override
	{
		LevelManager* levelManager = LevelManager::getInstance();
		if (this->active)
		{
			velocity = { -levelManager->SCROLLING_SPEED * deltaTime * this->speed, (sin(position.x / 75)) * ((1.5f *WindowConfig::getInstance()->SIZE_Y)/1080)};
		}
		else
		{
			velocity = { -levelManager->SCROLLING_SPEED * deltaTime, 0 };
		}
		this->position += velocity;
		this->hitbox.setPosition(this->position);
	}
};

class Wheel : public Enemy
{
public:
	Wheel(sf::Vector2f position_)
	{
		position = position_;
		color = sf::Color::Yellow;

		initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
		initProperties(75, 10, 1.f, true, 1.f);
	}

	void updateShoot(float deltaTime) override
	{
		if (!this->isOnCooldown() && this->canShoot)
		{
			if (!this->active) return; //returns if not active

			//reset cooldown
			this->shootCooldown = 0.f;

			BulletManager* bulletManager = BulletManager::getInstance();
			bulletManager->spawnbullet(this, { this->position }, { -1, 0}, 2 * this->speed);
			bulletManager->spawnbullet(this, { this->position }, { 1, 0 }, 2 * this->speed);
			bulletManager->spawnbullet(this, { this->position }, { 0, 1 }, 2 * this->speed);
			bulletManager->spawnbullet(this, { this->position }, { 0, -1 }, 2 * this->speed);
		}
		else
		{
			this->shootCooldown += deltaTime;
		}

		this->hitbox.rotate(1);
	}
};

class Swarm : public Enemy
{
public:
	Swarm(sf::Vector2f position_)
	{
		position = position_;
		color = sf::Color::Cyan;

		initHitbox({ WindowConfig::getInstance()->SIZE_Y / 9.f, WindowConfig::getInstance()->SIZE_Y / 9.f });
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