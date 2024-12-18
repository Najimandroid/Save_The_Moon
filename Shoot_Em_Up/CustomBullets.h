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
	bool deactivated;
	Entity* target;
public:
	HomingBullet(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_);

	void updatePosition(float deltaTime) override;
};

class DefaultBoss : public Bullet
{
private:
	Entity* target;
public:
	DefaultBoss(sf::Vector2f position_, sf::Vector2f direction_);
};

class HomingBulletBoss : public Bullet
{
private:
	bool deactivated;
	Entity* target;
public:
	HomingBulletBoss(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_);

	void updatePosition(float deltaTime) override;
};
