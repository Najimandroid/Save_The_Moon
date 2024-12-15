#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Window.h"

#include  <SFML/Graphics.hpp>

#include <iostream>
#include <thread>

//--------------------//* BULLET *\\--------------------\\

//* BOOLEANS *\\

bool Bullet::collided(Entity* entity)
{

	if (dynamic_cast<Enemy*>(this->getOwner()) && dynamic_cast<Enemy*>(entity)) { return false; } //ignore if from same type
	if (dynamic_cast<Player*>(this->getOwner()) && dynamic_cast<Player*>(entity)) { return false; } //ignore if from same type

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

//--------------------//* BULLET MANAGER *\\--------------------\\

//* FUNCTIONS *\\

void BulletManager::checkCollisions(Entity* entity)
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet == nullptr) { index++;  continue; }

		if (bullet->collided(entity) && entity != bullet->getOwner())
		{
			Player* player = dynamic_cast<Player*>(entity);
			if (player) {
				if (player->isOnHitCooldown()) return;
				std::cout << "-" << bullet->getDamage() << "HP\n";
			}

			entity->updateHealth(-(bullet->getDamage())); // -x hp

			//delete
			bullet->setNullOwner();
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

Bullet* BulletManager::spawnbullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed)
{

	Bullet* newBullet = new Bullet(20, speed * WindowConfig::getInstance()->SIZE_X/192, position, direction);
	this->bullets.push_back(newBullet);
	newBullet->setOwner(owner);
	newBullet->setColor(owner->getColor());
	return newBullet;

} 

Bullet* BulletManager::spawnbullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed, sf::Vector2f textureCoords)
{

	Bullet* newBullet = new Bullet(20, speed * WindowConfig::getInstance()->SIZE_X / 192, position, direction, textureCoords);
	this->bullets.push_back(newBullet);
	newBullet->setOwner(owner);
	newBullet->setColor(owner->getColor());
	return newBullet;
}


void BulletManager::moveBullet(float deltaTime, Bullet* bullet)
{
	LevelManager* levelManager = LevelManager::getInstance();
	//if (bullet == nullptr || bullet->getOwner() == nullptr) { std::cout << "erreur lors du mouvement d'un projectile\n"; return; }

	//make them move

	bullet->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * bullet->getSpeed() * bullet->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
						, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime* bullet->getSpeed()* bullet->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
	bullet->setPosition(bullet->getPosition() + bullet->getVelocity());

	//make them follow the scrolling speed

	bullet->setVelocity({ -levelManager->SCROLLING_SPEED * deltaTime, 0 });
	bullet->setPosition(bullet->getPosition() + bullet->getVelocity());

	bullet->getHitbox().setPosition(bullet->getPosition());
}

void BulletManager::despawnBullets()
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet == nullptr) { index++;  continue;; }

		if (bullet->getPosition().x > WindowConfig::getInstance()->SIZE_X || bullet->getPosition().x < 0)
		{
			//delete
			bullet->setNullOwner();
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

//* GRAPHICS *\\

bool BulletManager::loadTexture()
{
	if (!this->texture.loadFromFile("assets/textures/Bullets.png")) return false;
	return true;
}

void BulletManager::drawBullets(sf::RenderWindow& window)
{
	for (Bullet* adress : this->bullets)
	{
		sf::Sprite body;
		body.setTexture(texture);
		body.setScale({ .65f, .65f });

		body.setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * LevelManager::getInstance()->TILE_SIZE / 2,
			adress->getTextureCoords().y * LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2));


		body.setOrigin({ 30 / 2.f }, { 30 / 2.f }); //idk if it is the correct origin
		body.setPosition(adress->getPosition());

		window.draw(body);
	}
}

//* UPDATING *\\

void BulletManager::updatePositions(float deltaTime)
{
	for (Bullet* adress : this->bullets)
	{
		if (adress == nullptr) { continue; }

		this->moveBullet(deltaTime, adress);
	}
}

void BulletManager::updateOwners(Entity* owner) //Updates null owners
{
	for (Bullet* adress : this->bullets)
	{
		if (adress == nullptr) { continue; }

		if (adress->getOwner() == owner)
		{
			adress->setNullOwner();
		}
	}
}