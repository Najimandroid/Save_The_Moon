#include "Wall.h"
#include "Enemy.h"
#include "Level.h"

#include  <SFML/Graphics.hpp>
#include <iostream>

bool LevelManager::loadLevel(int levelIndex)
{
	if (!this->levelImage.loadFromFile("assets/levels/TestLevel.png"))  //this->levels.at(size_t(levelIndex))
	{
		std::cout << "FAILED LOADING LEVEL: " << levelIndex << '\n';
		return false;
	}

	WallManager* wallManager = WallManager::getInstance();
	EnemyManager* enemyManager = EnemyManager::getInstance();

	for (int x = 0; x < this->levelImage.getSize().x; x++)
	{
		for (int y = 0; y < this->levelImage.getSize().y; y++)
		{
			sf::Vector2f SPAWN_POSITION = { TILE_SIZE * float(x), TILE_SIZE * float(y) };

			if(this->levelImage.getPixel(x, y) == sf::Color::Black)
			{
				wallManager->spawnWall( SPAWN_POSITION , { TILE_SIZE , TILE_SIZE });
			}
			else
			if (this->levelImage.getPixel(x, y) == sf::Color::Red) 
			{
				enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SNIPER);
			}
			else
			if (this->levelImage.getPixel(x, y) == sf::Color::Yellow)
			{
				enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::WHEEL);
			}
		}
	}

	return true;
}