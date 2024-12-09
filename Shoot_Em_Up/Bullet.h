#pragma once
#include "Entity.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Bullet
{
private:
	float damage;
	float speed;
	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::RectangleShape hitbox;

	Entity* owner;

public:
	Bullet(float damage_, float speed_, sf::Vector2f position_, sf::Vector2f velocity_) :
		damage(damage_), speed(speed_), position(position_), velocity(velocity_), owner(nullptr)
	{
		sf::RectangleShape hitbox_(sf::Vector2f(10, 10));
		hitbox = hitbox_;
		hitbox.setPosition(position);
	}

	//* GET *\\

	float getSpeed() const { return speed; }
	float getDamage() { return damage; }

	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getVelocity() const { return velocity; }

	sf::RectangleShape& getHitbox() { return hitbox; }

	Entity* getOwner() { return owner; }

	//* SET *\\

	void setPosition(sf::Vector2f newPosition) { position = newPosition; }
	void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	void setOwner(Entity* owner_) { owner = owner_; }

	//* BOOLEANS *\\

	bool collided(Entity* obstacle);
};



class BulletManager
{
private:
	static BulletManager* instance;

	std::vector <Bullet*> bullets;

	BulletManager() {}
public:
	static BulletManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new BulletManager();
		}
		return instance;
	}

	Bullet* spawnbullet(Entity* owner, sf::Vector2f position, float speed);

	void moveBullet(float deltatime, Bullet* bullet);

	void despawnBullets();

	void drawBullets(sf::RenderWindow& window);
	void updatePositions(float deltaTime);

	std::vector <Bullet*> getBullets()
	{
		return bullets;
	}


	void checkCollisions(Entity* obstacle);
};