#pragma once

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

public:
	Bullet(float damage_, float speed_, sf::Vector2f position_ , sf::Vector2f velocity_) : 
		damage(damage_), speed(speed_), position(position_), velocity(velocity_) {}

	sf::Vector2f getPosition() const
	{
		return position;
	}

	sf::Vector2f getVelocity() const
	{
		return velocity;
	}

	void setPosition(sf::Vector2f newPosition)
	{
		position = newPosition;
	}

	void setVelocity(sf::Vector2f newVelocity)
	{
		velocity = newVelocity;
	}

	float getSpeed() const
	{
		return speed;
	}
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

	Bullet* spawnbullet(sf::Vector2f position, float speed);

	void movebullet(float deltatime, Bullet* bullet);

	void colisionbullet();

	void despawnbullet();

	void drawBullets(sf::RenderWindow& window);
	void updatePositions(float deltaTime);

	std::vector <Bullet*> getBullets()
	{
		return bullets;
	}
};