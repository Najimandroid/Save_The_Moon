#include "Wall.h"
#include "Enemy.h"
#include "Level.h"
#include "Background.h"

#include  <SFML/Graphics.hpp>
#include <iostream>

bool LevelManager::loadLevel(int levelIndex)
{
	if (!this->levelImage.loadFromFile("assets/levels/TestLevel.png"))  //this->levels.at(size_t(levelIndex))
	{
		std::cout << "FAILED LOADING LEVEL: " << levelIndex << '\n';
		return false;
	}

	sf::Texture layer1, layer2, layer3;
	layer1.loadFromFile("assets/backgrounds/Level_1/Layer1.png"); layer2.loadFromFile("assets/backgrounds/Level_1/Layer2.png"); layer3.loadFromFile("assets/backgrounds/Level_1/Layer3.png");
	std::vector<sf::Texture> textures_ =
	{
		layer1,
		layer2,
		layer3,
	};

	this->currentBackground = new Background(textures_);

	WallManager* wallManager = WallManager::getInstance();
	EnemyManager* enemyManager = EnemyManager::getInstance();

	for (int x = 0; x < this->levelImage.getSize().x; x++)
	{
		for (int y = 0; y < this->levelImage.getSize().y; y++)
		{
			sf::Vector2f SPAWN_POSITION = { TILE_SIZE * float(x), TILE_SIZE * float(y) };

			if(this->levelImage.getPixel(x, y) == sf::Color::Black)
			{
				Wall* newWall = wallManager->spawnWall( SPAWN_POSITION , { TILE_SIZE , TILE_SIZE });
				newWall->setTextureCoords({ 0, 0 });
			}
			else
			if (this->levelImage.getPixel(x, y) == sf::Color::Red) 
			{
				enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::DEFAULT);
			}
			else
			if (this->levelImage.getPixel(x, y) == sf::Color::Yellow)
			{
				enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SNIPER);
			}
		}
	}

	return true;
}