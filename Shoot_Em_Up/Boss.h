#pragma once

#include "Enemy.h"
#include "Window.h"
#include "Bullet.h"
#include "CustomBullets.h"
#include "Player.h"
#include "HealthBar.h"

#include "SFML/Graphics.hpp"
#include <iostream>
#include <functional>

// ATTACKS
void Attack_1(Enemy* entity);
void Attack_2(Enemy* entity);
void Attack_3(Entity* entity);


// CLASS
class Boss : public Enemy
{
private:
	float x = 0.f;
	bool healthBarSpawned = false;

	std::vector<std::function<void(Enemy*)>> attacks = { Attack_1 , Attack_2, Attack_3 };

public:
	Boss(sf::Vector2f position_);

	virtual void updatePosition(float deltaTime) override;
	virtual void updateShoot(float deltaTime) override;
};
