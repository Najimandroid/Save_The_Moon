#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>


class Player
{
private:
	int health;
	sf::Vector2f position;

	//Physics
	sf::Vector2f velocity;
	float acceleration;
	float drag;

	//Core

	void initPhysics();

public:

	Player(int health_, sf::Vector2f position_) : health(health_), position(position_) {}

};
