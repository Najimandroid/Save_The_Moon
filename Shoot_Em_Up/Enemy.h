#pragma once

#include <vector> 
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	//Main Properties
	float health;
	float damage;

	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;

public:

	Enemy(float health_, float damage_, sf::Vector2f position_, float speed_)
	{
		init(health_, damage_, position_, speed_);
	}

	sf::Vector2f getPosition() const
	{
		return position;
	}

	void init(float health_, float damage_, sf::Vector2f position_, float speed_);
	void updatePosition(float deltaTime);
};