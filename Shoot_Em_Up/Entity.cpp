#include "Entity.h"
#include "Bullet.h"
#include  <SFML/Graphics.hpp>

#include <vector> 
#include <iostream>

//* BOOLEANS *\\

bool Entity::isDead()
{
	return (this->health <= 0);
}

bool Entity::isOnCooldown()
{
	return (this->shootCooldown < this->shootCooldownMax);
}

//* UPDATING *\\

void Entity::updateHealth(float value)
{
	this->health += value;
}

void Entity::updatePosition(float deltaTime)
{
	velocity = { -20 * deltaTime * this->speed, 0 };
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

void Entity::update(float deltaTime)
{
	this->updatePosition(deltaTime);
	this->updateShoot(deltaTime);
}

void Entity::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown())
	{
		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnbullet({ this->position }, this->speed);
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

//* INITIALIZATION *\\

void Entity::initPosition(sf::Vector2f position_) { this->position = position_, this->velocity = { 0, 0 }; }

void Entity::initHitbox(sf::Vector2f hitboxSize_) 
{
	sf::RectangleShape hitbox_(sf::Vector2f(hitboxSize_.x, hitboxSize_.y));
	this->hitbox = hitbox_;
	this->hitbox.setPosition(this->position);
}

void Entity::initProperties(float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
	this->health = health_; this->damage = damage_; this->speed = speed_; this->canShoot = canShoot_, this->shootCooldownMax = cooldownSeconds_;
}

//* CONSTRUCTOR *\\

Entity::Entity(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
	this->initPosition(position_);
	this->initHitbox(hitboxSize_);
	this->initProperties(health_, damage_, speed_, canShoot_, cooldownSeconds_);
}

Entity::Entity()
{
	this->initPosition({0, 0});
	this->initHitbox({0, 0});
	this->initProperties(0, 0, 0, false, 0);
}