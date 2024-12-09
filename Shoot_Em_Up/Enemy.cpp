#include "Enemy.h"
#include "Bullet.h"
#include  <SFML/Graphics.hpp>

#include <vector> 
#include <iostream>

void Enemy::updatePosition(float deltaTime)
{
	velocity = { -20 * deltaTime * this->speed, 0 };
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

Enemy* EnemyManager::spawnEnemy(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	Enemy* newEnemy = new Enemy(position_, { 50, 50 }, health_, damage_, speed_, true, 2.f);
	this->enemies.push_back(newEnemy);
	return newEnemy;
}

void EnemyManager::drawEnemies(sf::RenderWindow& window)
{
	for (Enemy* adress : this->enemies)
	{
		adress->draw(window, { 50, 50 }, sf::Color::Red);
	}
}

void EnemyManager::updatePositions(float deltaTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->updatePosition(deltaTime);
	}
}

void EnemyManager::updateStates()
{
	//std::cout << "[ ";

	for (auto it = this->enemies.begin(); it != this->enemies.end(); )
	{
		Enemy* enemy = *it;
		//std::cout << enemy->getHealth() << ", ";

		if (enemy->isDead()) {
			// delete enemy if dead
			delete enemy;
			it = this->enemies.erase(it);
		}
		else {
			++it;  // updates only if the enemy is deleted
		}
	}

	//std::cout << " ]\n";
}

void EnemyManager::update(float deltaTime)
{
	this->updatePositions(deltaTime);
	this->updateStates();

	for (Enemy* enemy : this->enemies)
	{
		enemy->update(deltaTime);
	}
}

Enemy::Enemy(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
	this->initPosition(position_);
	this->initHitbox(hitboxSize_);
	this->initProperties(health_, damage_, speed_, canShoot_, cooldownSeconds_);
}