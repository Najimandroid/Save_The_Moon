#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>

namespace plr {

	//sf::RectangleShape* createPlayer(sf::Vector2f);

	class Player
	{
	private:
		int health;

	public:
		Player(int health_) : health(health_) {}

	};

}