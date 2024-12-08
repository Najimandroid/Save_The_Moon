#pragma once

#include <iostream>
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

	float shootCooldown;
	float shootCooldownMax;

	//Movement keys
	typedef std::vector<sf::Keyboard::Key> KeyVector;

	KeyVector upKeys = { sf::Keyboard::Key::Z, sf::Keyboard::Key::Up };
	KeyVector downKeys = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
	KeyVector leftKeys = { sf::Keyboard::Key::Q, sf::Keyboard::Key::Left };
	KeyVector rightKeys = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };

	KeyVector shootKeys = { sf::Keyboard::Key::Space };

public:

	Player(float health_, float cooldownSeconds_, sf::Vector2f position_);

	sf::Vector2f getPosition() const
	{
		return position;
	}

	void init(float health_, float cooldownSeconds_, sf::Vector2f position_);
	void update(float deltaTime);

	bool canShoot() const;

	void updateShoot(float deltaTime);
	void updatePosition(float deltaTime);
};