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
}

Enemy::Enemy(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	Enemy::init(health_,damage_,position_, speed_);
}

Enemy* EnemyManager::spawnEnemy(float health_, float damage_, sf::Vector2f position_, float speed_)
{
	Enemy* newEnemy = new Enemy(health_, damage_, position_, speed_);
	this->enemies.push_back(newEnemy);
	return newEnemy;
}

void EnemyManager::drawEnemies(sf::RenderWindow& window)
{
	for (Enemy* adress : this->enemies)
	{
		sf::RectangleShape boule(sf::Vector2f(50, 50));
		boule.setFillColor(sf::Color::Red);
		boule.setPosition(adress->getPosition());
		window.draw(boule);
	}
}

void EnemyManager::updatePositions(float deltaTime)
{
	for (Enemy* adress : enemies)
	{
		adress->updatePosition(deltaTime);
	}
}