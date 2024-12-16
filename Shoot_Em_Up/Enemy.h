#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "Level.h"
#include "Player.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

enum EnemyType
{
	DEFAULT, TANK, SNIPER, MOUTH, GIGA_MOUTH, SWARM, WAVE, WHEEL, TURRET_UP, TURRET_DOWN, TURRET_LEFT, TURRET_RIGHT, SPIKE, HOMING
};

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_, sf::Vector2f textureCoords_);
	Enemy() {};

	bool collided(Entity* obstacle);

	void updatePosition(float deltaTime) override;

	sf::Vector2f normalize(const sf::Vector2f& vector) {
		
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (length > 0) {
			return sf::Vector2f(vector.x / length, vector.y / length);
		}
		return sf::Vector2f(0.f, 0.f);
	}
};


class EnemyManager
{
private:
	static EnemyManager* instance;

	sf::Texture texture;
	std::vector <Enemy*> enemies;

	EnemyManager() { if (!loadTexture()) std::cout << "Enemies texture not loaded!"; }
public:
	static EnemyManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new EnemyManager();
		}
		return instance;
	}

	std::vector <Enemy*> getEnemies()
	{
		return enemies;
	}

	Enemy* spawnEnemy(sf::Vector2f position_, float health_, float damage_, float speed_);
	Enemy* spawnEnemy(sf::Vector2f position, EnemyType enemyType);

	bool loadTexture();
	void drawEnemies(sf::RenderWindow& window);
	void updatePositions(float deltaTime);
	void updateStates();
	
	void checkCollisions(Entity* entity);

	void update(float deltaTime);
};