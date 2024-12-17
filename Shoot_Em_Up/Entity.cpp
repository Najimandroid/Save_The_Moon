#include "Entity.h"
#include "Bullet.h"
#include "Player.h"
#include "Level.h"
#include "Window.h"

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
		velocity = { levelManager->SCROLLING_SPEED * deltaTime * this->speed * 1920 / WindowConfig::getInstance()->SIZE_X, 0 };
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
	if (this->position.x <= (WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X/96)) { this->active = true; }
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
		bulletManager->spawnBullet(this, { this->position }, { -1, 0 }, 2 * this->speed * 1920 / WindowConfig::getInstance()->SIZE_X, {0, 1});
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

void Entity::draw(sf::RenderWindow& window, sf::Texture texture, sf::Vector2f textureCoords)
{
	if (this->getPosition().x >= WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X / 10) { return; }

	this->sprite.setOrigin({ 30 / 2.f }, { 30 / 2.f });
	this->sprite.setPosition(this->getPosition());

	window.draw(this->sprite);
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
	this->health = health_; this->damage = damage_; this->speed = speed_ * WindowConfig::getInstance()->SIZE_X / WindowConfig::getInstance()->SIZE_X ; this->canShoot = canShoot_, this->shootCooldownMax = cooldownSeconds_; this->active = false;
}

//* CONSTRUCTOR *\\

Entity::Entity(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_, sf::Vector2f textureCoords_)
{
	this->initPosition(position_);
	this->initHitbox({ WindowConfig::getInstance()->SIZE_Y/hitboxSize_.x, WindowConfig::getInstance()->SIZE_Y/hitboxSize_.y });
	this->initProperties(health_, damage_, speed_, canShoot_, cooldownSeconds_);

	this->textureCoords = textureCoords_;
}

Entity::Entity()
{
	this->initPosition({ 0, 0 });
	this->initHitbox({ 0, 0 });
	this->initProperties(0, 0, 0, false, 0);
	this->color = sf::Color::White;
	this->textureCoords = { 0, 0 };
}

Entity::~Entity() {}

//Entity::~Entity()
//{
	//idk
//}