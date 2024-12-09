#pragma once
#include "Entity.h"

#include <iostream>
#include <vector> 
#include <SFML/Graphics.hpp>


class Player : public Entity
{
private:

	//* CONTROL KEYS *\\

	typedef std::vector<sf::Keyboard::Key> KeyVector;

	KeyVector upKeys = { sf::Keyboard::Key::Z, sf::Keyboard::Key::Up };
	KeyVector downKeys = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
	KeyVector leftKeys = { sf::Keyboard::Key::Q, sf::Keyboard::Key::Left };
	KeyVector rightKeys = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };

	KeyVector shootKeys = { sf::Keyboard::Key::Space };

public:
	Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);

	void updateShoot(float deltaTime) override;
	void updatePosition(float deltaTime) override;
};