#include "Bullet.h"
#include "Entity.h"
#include "Player.h"

#include  <SFML/Graphics.hpp>

#include <iostream>
#include <thread>
#include <type_traits>

bool Bullet::collided(Entity* entity)
{
	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

void BulletManager::checkCollisions(Entity* entity)
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet->collided(entity) && entity != bullet->getOwner())
		{
			if (dynamic_cast<Player*>(entity)) {
				std::cout << "-" << bullet->getDamage() << "HP\n";
			}
			
			entity->updateHealth( -(bullet->getDamage()) ); // -x hp

			//delete
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
	return newBullet;

}


void BulletManager::moveBullet(float deltaTime, Bullet* bullet)
{
	if (dynamic_cast<Player*>(bullet->getOwner())) {
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
		if (bullet->getPosition().x > 1900)
		{
			//delete
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

void BulletManager::drawBullets(sf::RenderWindow& window)
{
	for (Bullet* adress : this->bullets)
	{
		sf::RectangleShape body_(sf::Vector2f(10, 10));
		body_.setFillColor(sf::Color::White);
		body_.setPosition(adress->getPosition());
		window.draw(body_);
	}
}

void BulletManager::updatePositions(float deltaTime)
{
	for (Bullet* adress : this->bullets)
	{
		this->moveBullet(deltaTime, adress);
	}
}