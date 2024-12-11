#pragma once

#include <iostream>
#include <vector> 
#include <SFML/Graphics.hpp>


class Entity
{
protected:

	//* PROPERTIES *\\

	float health;
	float damage;

	float speed;

	sf::Vector2f position;
	sf::Vector2f velocity;

	float shootCooldown;
	float shootCooldownMax;

	bool canShoot;
	bool active;

	sf::RectangleShape hitbox;

	sf::Color color;

public:

	//* CONSTRUCTOR | DESTRUCTOR *\\

	Entity(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);
	Entity();

	virtual ~Entity() = 0;

	//* GET *\\

	sf::Vector2f getPosition() const { return position; }
	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Color getColor() { return color; }
	float getHealth() const { return health; }
	float getSpeed() const { return speed; }
	float getDamage() const { return damage; }
	bool getActive() const { return active; }

	//* SET *\\

	void setPosition(sf::Vector2f newPosition) { position = newPosition; }
	void setActive(bool newState) { active = newState; }

	//* INIT *\\

	void initPosition(sf::Vector2f position_);
	void initHitbox(sf::Vector2f hitboxSize_);
	void initProperties(float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);

	//* BOOL *\\

	bool isDead();
	bool isPlayer();
	bool isOnCooldown();

	//* UPDATE *\\

	void updateHealth(float value);
	void update(float deltaTime);
	virtual void updatePosition(float deltaTime);
	virtual void updateShoot(float deltaTime);
	virtual void updateState();

	//* GRAPHICS *\\

	void draw(sf::RenderWindow& window, sf::Color color);
};