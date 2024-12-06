#include "Enemy.h"

#include <vector> 
#include <SFML/Graphics.hpp>

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