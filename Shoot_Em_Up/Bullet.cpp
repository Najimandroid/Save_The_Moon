#include "Bullet.h"
#include "Player.h"
#include  <SFML/Graphics.hpp>
#include <iostream>


Bullet* BulletManager::spawnbullet(sf::Vector2f position)
{
		
	Bullet* newBullet = new Bullet(1, 50, { 0,0 }, position + sf::Vector2f{ 50, 0 });
	/*std::cout << "Balle créé";*/ 
	this->balles.push_back(newBullet);
	return newBullet;


}

void BulletManager::movebullet(float deltaTime, Bullet*bullet)
{
	bullet->setVelocity(sf::Vector2f{ 20 * deltaTime * bullet->getSpeed() , 0 });
	bullet->setPosition(bullet->getPosition() + bullet->getVelocity());
}

void BulletManager::colisionbullet()
{

}

void BulletManager::despawnbullet()
{
	for (Bullet* bullett : balles)
	{
		if (bullett->getPosition().x > 1900)
		{
			auto it = std::find(balles.begin(), balles.end(), bullett);
			if (it != balles.end())
			{
				balles.erase(it);
				delete bullett;
			}
		}
	}
}