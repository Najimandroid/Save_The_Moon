#include "CustomBullets.h"

//* HOMING BULLET*\\

HomingBullet::HomingBullet(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_)
{
	position = position_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 76, WindowConfig::getInstance()->SIZE_Y / 76));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 76 / 2.f, WindowConfig::getInstance()->SIZE_Y / 76 / 2.f));
	hitbox.setPosition(position);

	this->setDamage(30);
	speed = 20;

	lifeTimeMax = 30;

	target = target_;

	owner = nullptr;
	color = sf::Color::Green;

	textureCoords = { 3, 1 };
	deactivated = false;
}

void HomingBullet::updatePosition(float deltaTime)
{
	if (this->position.x < this->target->getPosition().x || deactivated) {
		direction = { -1, 0 };

		this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime * this->speed/8, 0 });
		this->setPosition(this->getPosition() + this->getVelocity());
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

	//std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

	this->setDamage(15);
	speed = 40;

	lifeTimeMax = 5;

	target = nullptr;

	owner = nullptr;
	color = sf::Color::Green;

	textureCoords = { 4, 0 };
}

//* SHRIMP BOSS BULLET *\\

Shrimp::Shrimp(sf::Vector2f position_, sf::Vector2f direction_)
{
	position = position_;
	direction = direction_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17, WindowConfig::getInstance()->SIZE_Y / 17));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17 / 2.f, WindowConfig::getInstance()->SIZE_Y / 17 / 2.f));
	hitbox.setPosition(position);

	//std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

	this->setDamage(20);
	speed = 25;

	lifeTimeMax = 5;

	target = nullptr;

	owner = nullptr;
	color = sf::Color::Magenta;

	textureCoords = { 4, 3 };
	sinValue = .0f;
}

void Shrimp::updatePosition(float deltaTime)
{
	this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
				, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
	this->setPosition(this->getPosition() + this->getVelocity());

	this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, (float)(sin(sinValue) * 4.f)});
	this->setPosition(this->getPosition() + this->getVelocity());

	this->getHitbox().setPosition(this->getPosition());

	sinValue += .05f;
}

//* PUFFER *\\

Puffer::Puffer(sf::Vector2f position_, sf::Vector2f direction_, Entity* owner_, Entity* target_)
{
	position = position_;
	direction = direction_;
	owner = owner_;
	target = target_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17, WindowConfig::getInstance()->SIZE_Y / 17));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 17 / 2.f, WindowConfig::getInstance()->SIZE_Y / 17 / 2.f));
	hitbox.setPosition(position);

	//std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

	this->setDamage(20);
	speed = 15;

	lifeTimeMax = 15;

	
	color = sf::Color::Magenta;

	textureCoords = { 3, 2 };
}

void Puffer::updatePosition(float deltaTime)
{

	if (this->position.x < this->target->getPosition().x + 300) 
	{
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), { -1, 0 }, 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), { 0, -1 }, 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), { 1, 0 }, 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), { 0, 1 }, 3, { 2, 2 });

		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.5, .5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .5, -.5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .5, .5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.5, -.5 }), 3, { 2, 2 });

		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.25, .5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.25, -.5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .25, .5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .25, -.5 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.5, -.25 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .5, -.25 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ -.5, .25 }), 3, { 2, 2 });
		BulletManager::getInstance()->spawnBullet(owner, this->getPosition(), normalize({ .5, .25 }), 3, { 2, 2 });


		this->setPosition({ -900, 0 });
	}

	this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
					, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
	this->setPosition(this->getPosition() + this->getVelocity());

	this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, 0 });
	this->setPosition(this->getPosition() + this->getVelocity());

	this->getHitbox().setPosition(this->getPosition());
}

//* HOMING BOSS BULLET *\\

HomingBulletBoss::HomingBulletBoss(sf::Vector2f position_, Entity* target_, sf::Vector2f textureCoords_)
{
	position = position_;

	sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 24, WindowConfig::getInstance()->SIZE_Y / 24));
	hitbox = hitbox_;
	hitbox.setOrigin(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 24 / 2.f, WindowConfig::getInstance()->SIZE_Y / 24 / 2.f));
	hitbox.setPosition(position);

	//std::cout << this->hitbox.getPosition().x << ", " << this->hitbox.getPosition().y << std::endl;

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
		deactivated = true;
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
