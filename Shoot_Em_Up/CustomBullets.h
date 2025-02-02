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

class Shrimp : public Bullet
{
private:
	float sinValue;
	Entity* target;
public:
	Shrimp(sf::Vector2f position_, sf::Vector2f direction_);

	void updatePosition(float deltaTime) override;
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

class Puffer : public Bullet
{
private:
	Entity* target;
	Entity* owner;
public:
	Puffer(sf::Vector2f position_, sf::Vector2f direction_, Entity* owner_, Entity* target_);

	void updatePosition(float deltaTime) override;
};
