#include "Enemy.h"
#include  <SFML/Graphics.hpp>

#include <vector> 
#include <iostream>

void Enemy::init(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	this->health = health_;
	this->damage = damage_;
	this->position = position_;
	this->speed = speed_;
	this->velocity = { 0, 0 };
}

void Enemy::updatePosition(float deltaTime)
{
	velocity = { -20 * deltaTime * this->speed, 0 };
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

Enemy::Enemy(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	Enemy::init(health_,damage_,position_, speed_);
	sf::RectangleShape hitbox_(sf::Vector2f(50, 50));
	this->hitbox = hitbox_;
	this->hitbox.setPosition(this->position);
}

Enemy* EnemyManager::spawnEnemy(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	Enemy* newEnemy = new Enemy(health_, damage_, position_, speed_);
	this->enemies.push_back(newEnemy);
	return newEnemy;
}

void Enemy::updateHealth(float value)
{
	this->health += value;
}

bool Enemy::isDead()
{
	return (this->health <= 0);
}

void EnemyManager::drawEnemies(sf::RenderWindow& window)
{
	for (Enemy* adress : this->enemies)
	{
		sf::RectangleShape body_(sf::Vector2f(50, 50));
		body_.setFillColor(sf::Color::Red);
		body_.setPosition(adress->getPosition());
		window.draw(body_);
	}
}

void EnemyManager::updatePositions(float deltaTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->updatePosition(deltaTime);
	}
}

void EnemyManager::updateState()
{
	std::cout << "[ ";

	for (auto it = this->enemies.begin(); it != this->enemies.end(); ) 
		{
			Enemy* enemy = *it;
			std::cout << enemy->getHealth() << ", ";

			if (enemy->isDead()) {
				// delete enemy if dead
				delete enemy;
				it = this->enemies.erase(it);
			}
			else {
				++it;  // updates only if the enemy is deleted
			}
		}

	std::cout << " ]\n";
}

void EnemyManager::update(float deltaTime)
{
	this->updatePositions(deltaTime);
	this->updateState();
}