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
	Bullet(float D, float S, sf::Vector2f V,sf::Vector2f P) : damage(D), speed(S),velocity(V), position(P) {}
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
	BulletManager() {}
public:
	static BulletManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new BulletManager();
		}
		return instance;
	}

	std::vector <Bullet*> balles;

	Bullet*spawnbullet(sf::Vector2f position);
	void movebullet(float deltatime, Bullet* bullet);
	void colisionbullet();
	void despawnbullet();
};