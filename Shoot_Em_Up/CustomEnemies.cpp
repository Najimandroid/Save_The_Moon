#pragma once

#include "CustomEnemies.h"

//* TANK *\\

Tank::Tank(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Yellow;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 27.f, WindowConfig::getInstance()->SIZE_Y / 27.f });
	initProperties(300, 50, 1.5f, true, 5.f);
}

//* MOUTH *\\

Mouth::Mouth(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Yellow;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 14.f, WindowConfig::getInstance()->SIZE_Y / 14.f });
	initProperties(100, 20, 2.f, false, 0.f);

	textureCoords = { 3, 1 };
}

//* GIGA MOUTH *\\

GigaMouth::GigaMouth(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Yellow;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 9.f, WindowConfig::getInstance()->SIZE_Y / 9.f });
	initProperties(500, 100, 1.1f, false, 0.f);

	textureCoords = { 4, 1 };
}

//* SPIKE *\\

Spike::Spike(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Red;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(150, 35, 1.f, false, 0.f);

	textureCoords = { 1, 1 };
}

//* SNIPER *\\

Sniper::Sniper(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Magenta;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(50, 25, 1.75f, true, 3.f);

	textureCoords = { 2, 1 };
}

void Sniper::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		if (PlayerManager::getInstance()->getPlayers().empty()) { std::cout << "players empty\n"; return; }
		if (PlayerManager::getInstance()->getPlayers()[0] == nullptr) { std::cout << "sniper error\n"; return; }

		BulletManager* bulletManager = BulletManager::getInstance();

		bulletManager->spawnBullet(this, { this->position },
			normalize(
				{
				  (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
				, (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
				}
			),
			2 * this->speed, { 2, 1 });

	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

//* HOMING *\\

Homing::Homing(sf::Vector2f position_, Entity* target_)
{
	target = target_;

	position = position_;
	color = sf::Color::Magenta;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(50, 25, 1.2f, true, 3.f);

	textureCoords = { 2, 2 };
}

void Homing::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		if (PlayerManager::getInstance()->getPlayers().empty()) { std::cout << "players empty\n"; return; }
		if (this->target == nullptr) { std::cout << "huming error\n"; return; }

		BulletManager::getInstance()->spawnBullet(this, { this->position }, { -1, 0 }, HOMING_b, 2 * this->speed);

	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

//* TURRETS *\\

// UP

TurretUp::TurretUp(sf::Vector2f position_)
{
	position = position_;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(250, 10, 1.f, true, 1.f);

	textureCoords = { 1, 0 };
}

void TurretUp::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnBullet(this, { this->position }, normalize({ 0, -1 }), 2 * this->speed, { 1, 1 });
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

// DOWN

TurretDown::TurretDown(sf::Vector2f position_)
{
	position = position_;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(250, 10, 1.f, true, 1.f);

	textureCoords = { 2, 0 };
}

void TurretDown::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnBullet(this, { this->position }, normalize({ 0, 1 }), 2 * this->speed, { 1, 1 });
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

// RIGHT 

TurretRight::TurretRight(sf::Vector2f position_)
{
	position = position_;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(250, 10, 1.f, true, 1.f);

	textureCoords = { 3, 0 };
}

void TurretRight::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnBullet(this, { this->position }, normalize({ 1, 0 }), 2 * this->speed, { 1, 1 });
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

// LEFT

TurretLeft::TurretLeft(sf::Vector2f position_)
{
	position = position_;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(250, 10, 1.f, true, 1.f);

	textureCoords = { 4, 0 };
}

void TurretLeft::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnBullet(this, { this->position }, normalize({ -1, 0 }), 2 * this->speed, { 1, 1 });
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

//* WAVE *\\

Wave::Wave(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Red;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(100, 25, 2.f, true, 1.f);

	textureCoords = { 1, 2 };
}

void Wave::updatePosition(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	if (this->active)
	{
		velocity = { -levelManager->SCROLLING_SPEED * deltaTime * this->speed, (sin(position.x / 75)) * ((1.5f * WindowConfig::getInstance()->SIZE_Y) / 1080) };
	}
	else
	{
		velocity = { -levelManager->SCROLLING_SPEED * deltaTime, 0 };
	}
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

void Wave::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();
		bulletManager->spawnBullet(this, { this->position }, { -1, 0 }, 2 * this->speed * 1920 / WindowConfig::getInstance()->SIZE_X, { 1, 2 });
	}
	else
	{
		this->shootCooldown += deltaTime;
	}
}

//* WHEEL *\\

Wheel::Wheel(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Yellow;
	count = 0;
	textureCoords = { 0, 2 };

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f });
	initProperties(75, 10, 1.f, true, .5f);
}

void Wheel::updateShoot(float deltaTime)
{
	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		this->shootCooldown = 0.f;

		BulletManager* bulletManager = BulletManager::getInstance();

		if (count % 2 == 0)
		{
			bulletManager->spawnBullet(this, { this->position }, normalize({ -1, 0 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ 1, 0 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ 0, 1 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ 0, -1 }), 2 * this->speed, { 0, 2 });
		}
		else
		{
			bulletManager->spawnBullet(this, { this->position }, normalize({ -1, 1 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ 1, -1 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ -1, -1 }), 2 * this->speed, { 0, 2 });
			bulletManager->spawnBullet(this, { this->position }, normalize({ 1, 1 }), 2 * this->speed, { 0, 2 });
		}

		count++;
	}
	else
	{
		this->shootCooldown += deltaTime;
	}

	this->hitbox.rotate(2);
}

//* SWARM *\\

Swarm::Swarm(sf::Vector2f position_)
{
	position = position_;
	color = sf::Color::Cyan;

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 9.f, WindowConfig::getInstance()->SIZE_Y / 9.f });
	initProperties(10, 0, 6.f, false, 0.f);
}