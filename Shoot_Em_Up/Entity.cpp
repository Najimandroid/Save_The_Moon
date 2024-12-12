#include "Entity.h"
#include "Bullet.h"
#include "Player.h"
#include "Level.h"

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

bool Entity::isPlayer()
{
	return (dynamic_cast<Player*>(this));
}

//* UPDATING *\\

void Entity::updateHealth(float value)
{
	if (!this->active) return; // doesn't update health if the entity is inactive
	this->health += value;
}

void Entity::updatePosition(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	if (this->active)
	{
		velocity = { levelManager->SCROLLING_SPEED * deltaTime * this->speed, 0 };
	}
	else
	{
		velocity = { levelManager->SCROLLING_SPEED * deltaTime, 0 };
	}
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

void Entity::update(float deltaTime)
{
	if (this->position.x <= 2000) { this->active = true; }
	this->updatePosition(deltaTime);
	this->updateShoot(deltaTime);
	this->updateState(deltaTime);
}

void Entity::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		LevelManager* levelManager = LevelManager::getInstance();
		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnbullet(this, { this->position }, { -1, 0 }, 2 * this->speed);
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

void Entity::updateState(float deltaTime)
{
	if (this->isDead()) {
		// delete if dead
		delete this;
	}
}

//* GRAPHICS *\\

void Entity::draw(sf::RenderWindow& window, sf::Color color)
{
	sf::RectangleShape body_( this->getHitbox().getSize() );
	body_.setOrigin( this->getHitbox().getSize() / 2.f );
	body_.setFillColor(color);
	body_.setPosition(this->getPosition());
	window.draw(body_);
}

//* INITIALIZATION *\\

void Entity::initPosition(sf::Vector2f position_) { this->position = position_, this->velocity = { 0, 0 }; }

void Entity::initHitbox(sf::Vector2f hitboxSize_)
{
	sf::RectangleShape hitbox_(sf::Vector2f(hitboxSize_.x, hitboxSize_.y));
	this->hitbox = hitbox_;
	this->hitbox.setOrigin(hitboxSize_ / 2.f);
	this->hitbox.setPosition(this->position);
}

void Entity::initProperties(float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
	this->health = health_; this->damage = damage_; this->speed = speed_; this->canShoot = canShoot_, this->shootCooldownMax = cooldownSeconds_; this->active = false;
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
	this->initPosition({ 0, 0 });
	this->initHitbox({ 0, 0 });
	this->initProperties(0, 0, 0, false, 0);
	this->color = sf::Color::White;
}

Entity::~Entity() {}

//Entity::~Entity()
//{
	//idk
//}