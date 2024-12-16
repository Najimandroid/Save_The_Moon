#pragma once

#include  <SFML/Graphics.hpp>

#include "Bullet.h"
#include "Level.h"
#include "Window.h"

#include <iostream>
#include <cmath>

class HomingBullet : public Bullet
{
private:
	Entity* target;
public:
	HomingBullet(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_)
	{
		position = position_;

		sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 108, WindowConfig::getInstance()->SIZE_Y / 108));
		hitbox = hitbox_;
		hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 108 / 2.f, WindowConfig::getInstance()->SIZE_Y / 108 / 2.f));
		hitbox.setPosition(position);
		
		std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

		this->setDamage(10);
		speed = 15;

		lifeTimeMax = 5;

		target = target_;

		owner = nullptr;
		color = sf::Color::Green;

		textureCoords = textureCoords_;
	}

	void updatePosition(float deltaTime) override
	{
		direction = { 
				normalize(
					{
					  (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
					, (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
					}
		)};

		this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
				, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
		this->setPosition(this->getPosition() + this->getVelocity());


		this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, 0 });
		this->setPosition(this->getPosition() + this->getVelocity());

		this->getHitbox().setPosition(this->getPosition());
	}
};
