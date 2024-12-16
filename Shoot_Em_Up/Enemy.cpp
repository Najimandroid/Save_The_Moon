#include "Enemy.h"
#include "CustomEnemies.h"
#include "Boss.h"

#include "Bullet.h"
#include "Window.h"
#include "Level.h"
#include  <SFML/Graphics.hpp>

#include <vector> 
#include <iostream>

//--------------------//* ENEMY *\\--------------------\\

//* BOOLEANS *\\

bool Enemy::collided(Entity* entity)
{
	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

//* UPDATE *\\ 

void Enemy::updatePosition(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	if (this->active)
	{
		velocity = { -levelManager->SCROLLING_SPEED * deltaTime * this->speed, 0 };
	}
	else
	{
		velocity = { -levelManager->SCROLLING_SPEED * deltaTime, 0 };
	}
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

//* CONSTRUCTOR | DESTRUCTOR *\\

Enemy::Enemy(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_, sf::Vector2f textureCoords_)
{
	this->initPosition(position_);
	this->initHitbox(hitboxSize_);
	this->initProperties(health_, damage_, ((speed_ * WindowConfig::getInstance()->SIZE_X) / 1920), canShoot_, cooldownSeconds_);
	this->color = sf::Color::Red;
	this->textureCoords = textureCoords_;
}

//--------------------//* ENEMY MANAGER *\\--------------------\\

//* FUNCTIONS *\\ 

Enemy* EnemyManager::spawnEnemy(sf::Vector2f position_, float health_, float damage_, float speed_)
{
	Enemy* newEnemy = new Enemy(position_, { 50, 50 }, health_, damage_, speed_, true, 2.f, {0, 1});
	this->enemies.push_back(newEnemy);
	return newEnemy;
}

Enemy* EnemyManager::spawnEnemy(sf::Vector2f position_, EnemyType enemyType)
{
	Enemy* newEnemy = nullptr;

	switch (enemyType)
	{
		case DEFAULT: newEnemy = new Enemy(position_, { 50, 50 }, 50, 25, 1.5f, true, 2.f, {0, 1});  break;
		case TANK: newEnemy = new Tank(position_);  break;
		case SWARM: newEnemy = new Swarm(position_);  break;
		case WAVE: newEnemy = new Wave(position_); break;
		case WHEEL: newEnemy = new Wheel(position_); break;
		case SNIPER: newEnemy = new Sniper(position_); break;
		case TURRET_UP: newEnemy = new TurretUp(position_); break;
		case TURRET_DOWN: newEnemy = new TurretDown(position_); break;
		case TURRET_RIGHT: newEnemy = new TurretRight(position_); break;
		case TURRET_LEFT: newEnemy = new TurretLeft(position_); break;
		case SPIKE: newEnemy = new Spike(position_); break;
		case MOUTH: newEnemy = new Mouth(position_); break;
		case GIGA_MOUTH: newEnemy = new GigaMouth(position_); break;
		case HOMING: newEnemy = new Homing(position_, PlayerManager::getInstance()->getPlayers()[0]); break;


		case BOSS_1: newEnemy = new Boss(position_); break;
	}

	if (newEnemy == nullptr) 
	{ 
		std::cout << "CAN'T CREATE ENEMY OF TYPE " << std::to_string(enemyType) << '\n'; return spawnEnemy(position_, EnemyType::DEFAULT); 
	}

	this->enemies.push_back(newEnemy);
	return newEnemy;
}

//* GRAPHICS *\\ 

bool EnemyManager::loadTexture()
{
	if (!this->texture.loadFromFile("assets/textures/Enemies.png")) return false;
	return true;
}

void EnemyManager::drawEnemies(sf::RenderWindow& window)
{
	for (Enemy* adress : this->enemies)
	{
		adress->draw(window,this->texture, adress->getTextureCoords());
	}
}

//* UPDATING *\\ 

void EnemyManager::updatePositions(float deltaTime)
{
	for (Enemy* enemy : enemies)
	{
		enemy->updatePosition(deltaTime);
	}
}

void EnemyManager::updateStates()
{
	//std::cout << "[ ";

	for (auto it = this->enemies.begin(); it != this->enemies.end(); )
	{
		Enemy* enemy = *it;
		//std::cout << enemy->getHealth() << ", ";

		if (enemy->isDead()) {
			// delete enemy if dead
			BulletManager* bulletManager = BulletManager::getInstance();
			bulletManager->updateOwners(enemy);
			delete enemy;
			it = this->enemies.erase(it);
		}
		else {
			++it;  // updates only if the enemy is deleted
		}
	}

	//std::cout << " ]\n";
}

void EnemyManager::checkCollisions(Entity* entity)
{
	for (Enemy* enemy : this->enemies)
	{

		if (enemy->collided(entity) && !dynamic_cast<Enemy*>(entity))
		{
			Player* player = dynamic_cast<Player*>(entity);
			if (player) {
				if (player->isOnHitCooldown()) return;
			}

			entity->updateHealth(-(enemy->getDamage())); // -x hp
		}
	}
}

void EnemyManager::update(float deltaTime)
{
	this->updatePositions(deltaTime);
	this->updateStates();

	for (Enemy* enemy : this->enemies)
	{
		if (enemy->getPosition().x <= WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X / LevelManager::getInstance()->TILE_SIZE ) { enemy->setActive(true); }
		enemy->updateShoot(deltaTime);
	}
}
