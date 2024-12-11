#include "Wall.h"
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

	for (int x = 0; x < levelImage.getSize().x; x++)
	{
		for (int y = 0; y < levelImage.getSize().y; y++)
		{
			if(levelImage.getPixel(x, y) == sf::Color::Black) 
			{
				wallManager->spawnWall({ TILE_SIZE * float(x), TILE_SIZE *float(y)}, { TILE_SIZE, TILE_SIZE });
			}
		}
	}

	return true;
}