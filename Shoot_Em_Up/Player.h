#pragma once

#include <vector> 
#include <SFML/Graphics.hpp>


class Player
{
private:
	//Main Properties
	float health;

	sf::Vector2f position;
	sf::Vector2f velocity;
    float speed;

	//Movement keys
	typedef std::vector<sf::Keyboard::Key> KeyVector;

	KeyVector upKeys = { sf::Keyboard::Key::Z, sf::Keyboard::Key::Up };
	KeyVector downKeys = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
	KeyVector leftKeys = { sf::Keyboard::Key::Q, sf::Keyboard::Key::Left };
	KeyVector rightKeys = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };

public:

	Player(float health_, sf::Vector2f position_);

	sf::Vector2f getPosition() const
	{
		return position;
	}

	void init(float health_, sf::Vector2f position_);

	void updatePosition(float deltaTime);

};
