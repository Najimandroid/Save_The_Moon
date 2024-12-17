#pragma once

#include "Enemy.h"

class Tank : public Enemy
{
public:
	Tank(sf::Vector2f position_);
};

class Mouth : public Enemy
{
public:
	Mouth(sf::Vector2f position_);
};

class GigaMouth : public Enemy
{
public:
	GigaMouth(sf::Vector2f position_);
};

class Spike : public Enemy
{
public:
	Spike(sf::Vector2f position_);
};

class Sniper : public Enemy
{
public:
	Sniper(sf::Vector2f position_);
	void updateShoot(float deltaTime) override;
};

class Homing : public Enemy
{
public:
	Homing(sf::Vector2f position_, Entity* target_);

	void updateShoot(float deltaTime) override;
};

class TurretUp : public Enemy
{
public:
	TurretUp(sf::Vector2f position_);

	void updateShoot(float deltaTime);
};

class TurretDown : public Enemy
{
public:
	TurretDown(sf::Vector2f position_);

	void updateShoot(float deltaTime) override;
};

class TurretRight : public Enemy
{
public:
	TurretRight(sf::Vector2f position_);

	void updateShoot(float deltaTime) override;
};

class TurretLeft : public Enemy
{
public:
	TurretLeft(sf::Vector2f position_);

	void updateShoot(float deltaTime) override;
};

class Wave : public Enemy
{
public:
	Wave(sf::Vector2f position_);

	void updatePosition(float deltaTime) override;
};

class Wheel : public Enemy
{
private:
	int count;
public:
	Wheel(sf::Vector2f position_);

	void updateShoot(float deltaTime) override;
};

class Swarm : public Enemy
{
public:
	Swarm(sf::Vector2f position_);
};