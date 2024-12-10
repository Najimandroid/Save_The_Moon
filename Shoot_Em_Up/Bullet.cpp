#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

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
			if (dynamic_cast<Player*>(entity)) {
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

Bullet* BulletManager::spawnbullet(Entity* owner, sf::Vector2f position, float speed)
{

	Bullet* newBullet = new Bullet(20, speed * 2, position, { 0,0 });
	this->bullets.push_back(newBullet);
	newBullet->setOwner(owner);
	newBullet->setColor(owner->getColor());
	return newBullet;

}

void BulletManager::moveBullet(float deltaTime, Bullet* bullet)
{
	//if (bullet == nullptr || bullet->getOwner() == nullptr) { std::cout << "erreur lors du mouvement d'un projectile\n"; return; }

	if (bullet->getOwner()->isPlayer()) {
		bullet->setVelocity(sf::Vector2f{ 20 * deltaTime * bullet->getSpeed() , 0 });
		bullet->setPosition(bullet->getPosition() + bullet->getVelocity());
		bullet->getHitbox().setPosition(bullet->getPosition());
	}
	else
	{
		bullet->setVelocity(sf::Vector2f{ -20 * deltaTime * bullet->getSpeed() * 2 , 0 });
		bullet->setPosition(bullet->getPosition() + bullet->getVelocity());
		bullet->getHitbox().setPosition(bullet->getPosition());
	}
}

void BulletManager::despawnBullets()
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet == nullptr) { index++;  continue;; }

		if (bullet->getPosition().x > 1900 || bullet->getPosition().x < 0)
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

void BulletManager::drawBullets(sf::RenderWindow& window)
{
	for (Bullet* adress : this->bullets)
	{
		sf::RectangleShape body_(sf::Vector2f(10, 10));
		body_.setFillColor(adress->getColor());
		body_.setOrigin(adress->getHitbox().getSize() / 2.f);
		body_.setPosition(adress->getPosition());
		window.draw(body_);
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