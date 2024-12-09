#include "Bullet.h"
#include "Player.h"
#include  <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

bool Bullet::collided(Enemy* obstacle)
{
	sf::FloatRect  floatRect  = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = obstacle->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

void BulletManager::checkCollisions(Enemy* obstacle)
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet->collided(obstacle))
		{
			std::cout << "Touche: -" << bullet->getDamage() << "HP\n";
			obstacle->updateHealth(-bullet->getDamage()); // -x hp

			//delete
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

Bullet* BulletManager::spawnbullet(sf::Vector2f position, float speed)
{

	Bullet* newBullet = new Bullet(20, speed*2, position + sf::Vector2f{ 50, 0 }, { 0,0 });
	this->bullets.push_back(newBullet);
	return newBullet;

}


void BulletManager::moveBullet(float deltaTime, Bullet* bullet)
{
	bullet->setVelocity(sf::Vector2f{ 20 * deltaTime * bullet->getSpeed() , 0 });
	bullet->setPosition(bullet->getPosition() + bullet->getVelocity());
	bullet->getHitbox().setPosition(bullet->getPosition());
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
		sf::RectangleShape boule(sf::Vector2f(10, 10));
		boule.setFillColor(sf::Color::White);
		boule.setPosition(adress->getPosition());
		window.draw(boule);
	}
}

void BulletManager::updatePositions(float deltaTime)
{
	for (Bullet* adress : this->bullets)
	{
		this->moveBullet(deltaTime, adress);
	}
}