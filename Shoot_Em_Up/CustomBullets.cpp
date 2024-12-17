#include "CustomBullets.h"

//* HOMING BULLET*\\

HomingBullet::HomingBullet(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_)
{
	position = position_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 108, WindowConfig::getInstance()->SIZE_Y / 108));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 108 / 2.f, WindowConfig::getInstance()->SIZE_Y / 108 / 2.f));
	hitbox.setPosition(position);

	this->setDamage(10);
	speed = 60;

	lifeTimeMax = 5;

	target = target_;

	owner = nullptr;
	color = sf::Color::Green;

	textureCoords = textureCoords_;
}

void HomingBullet::updatePosition(float deltaTime)
{
	if (this->position.x < this->target->getPosition().x) {
		direction = { -1, 0 };

		this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, 0 });
		this->setPosition(this->getPosition() + this->getVelocity());
	}
	else
	{
		direction = {
		normalize(
			{
			  (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
			, (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
			}
		) };


		this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
				, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
		this->setPosition(this->getPosition() + this->getVelocity());
	}

	this->getHitbox().setPosition(this->getPosition());
}

//* DEFAULT BOSS BULLET *\\

DefaultBoss::DefaultBoss(sf::Vector2f position_, sf::Vector2f direction_)
{
	position = position_;
	direction = direction_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17, WindowConfig::getInstance()->SIZE_Y / 17));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17 / 2.f, WindowConfig::getInstance()->SIZE_Y / 17 / 2.f));
	hitbox.setPosition(position);

	std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

	this->setDamage(15);
	speed = 40;

	lifeTimeMax = 5;

	target = nullptr;

	owner = nullptr;
	color = sf::Color::Green;

	textureCoords = { 4, 0 };
}

//* HOMING BOSS BULLET *\\

HomingBulletBoss::HomingBulletBoss(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_)
{
	position = position_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 24, WindowConfig::getInstance()->SIZE_Y / 24));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 24 / 2.f, WindowConfig::getInstance()->SIZE_Y / 24 / 2.f));
	hitbox.setPosition(position);

	std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

	this->setDamage(10);
	speed = 18;

	lifeTimeMax = 20;

	target = target_;

	owner = nullptr;
	color = sf::Color::Green;

	textureCoords = { 4, 1 };

	deactivated = false;
}

void HomingBulletBoss::updatePosition(float deltaTime)
{

	if (this->position.x < this->target->getPosition().x || deactivated) {
		direction = { -1, 0 };

		//this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, 0 });
		//this->setPosition(this->getPosition() + this->getVelocity());
	}
	else if(!deactivated)
	{
		direction = {
		normalize(
			{
			  (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
			, (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - this->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - this->getPosition().y)))
			}
		) };
	}

	this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
		, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
	this->setPosition(this->getPosition() + this->getVelocity());

	this->getHitbox().setPosition(this->getPosition());
}