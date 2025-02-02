#pragma once

#include "Enemy.h"
#include "Window.h"
#include "Bullet.h"
#include "CustomBullets.h"
#include "Player.h"
#include "Music.h"
#include "HealthBar.h"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <functional>

// ATTACKS
void Attack_1(Enemy* entity);
void Attack_2(Enemy* entity);
void Attack_3(Entity* entity);

void ShrimpAttack_1(Entity* entity);
void ShrimpAttack_2(Entity* entity);


// CLASS
class Boss : public Enemy
{
private:
	float x = 0.f;
	bool healthBarSpawned = false;
	bool onRageMode = false;

	std::vector<std::function<void(Enemy*)>> attacks = {};

public:
	Boss(sf::Vector2f position_);
	Boss(sf::Vector2f position_, int levelIndex_);

	virtual void updatePosition(float deltaTime) override;
	virtual void updateShoot(float deltaTime) override;
};
