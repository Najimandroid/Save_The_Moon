#include "Wall.h"
#include "Player.h"
#include "Level.h"

#include  <SFML/Graphics.hpp>

bool Wall::collided(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize)
{
	sf::RectangleShape checkHitbox(entityHitboxSize);
	checkHitbox.setOrigin(entityHitboxSize / 2.f);
	checkHitbox.setPosition(targetPosition);

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = checkHitbox.getGlobalBounds();

	return(floatRect.intersects(otherFloatRect));
}

void Wall::initHitbox(sf::Vector2f hitboxSize_)
{
	sf::RectangleShape hitbox_(sf::Vector2f(hitboxSize_.x, hitboxSize_.y));
	this->hitbox = hitbox_;
	this->hitbox.setOrigin(hitboxSize_ / 2.f);
	this->hitbox.setPosition(this->position);
}

Wall* WallManager::spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize)
{
	Wall* newWall = new Wall(position, hitboxSize);
	this->walls.push_back(newWall);
	return newWall;
}

Wall* WallManager::spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize, bool isBreakable, float health)
{
	Wall* newWall = new Wall(position, hitboxSize, isBreakable, health);
	this->walls.push_back(newWall);
	return newWall;
}

sf::Vector2f WallManager::getWallsVelocity()
{
	return this->walls[0]->getVelocity();
}

void WallManager::drawWalls(sf::RenderWindow& window)
{
	for (Wall* adress : this->walls)
	{
		sf::RectangleShape body_(sf::Vector2f(adress->getHitbox().getSize()));
		body_.setFillColor(adress->getColor());
		body_.setOrigin(adress->getHitbox().getSize() / 2.f);
		body_.setPosition(adress->getPosition());
		window.draw(body_);
	}
}

void WallManager::updatePositions(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	for (Wall* wall : this->walls)
	{
		wall->setVelocity(sf::Vector2f{ -levelManager->SCROLLING_SPEED * deltaTime, 0 });
		wall->setPosition(wall->getPosition() + wall->getVelocity());
		wall->getHitbox().setPosition(wall->getPosition());
	}
}

bool WallManager::detectCollision(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize)
{
	for (Wall* wall : this->walls)
	{
		if (wall->collided(targetPosition, entityHitboxSize)) return true;
	}
	return false;
}