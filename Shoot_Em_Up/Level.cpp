#include "Wall.h"
#include "Enemy.h"
#include "Level.h"
#include "Background.h"

#include  <SFML/Graphics.hpp>
#include <iostream>

unsigned int LevelManager::colorToInt(const sf::Color& color)
{
	return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

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

			sf::Color color = this->levelImage.getPixel(x, y);
			unsigned int colorCode = colorToInt(color);

			switch (colorCode)
			{
			case 0x000000FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 0, 0 }); break;
			case 0x353535FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 1, 0 }); break;
			case 0x313131FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 2, 0 }); break;
			case 0x737373FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 0, 1 }); break;
			case 0xFF0000FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::MOUTH); break;
			case 0xFFFF00FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SNIPER); break;
			case 0x0000FFFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SPIKE); break;
			}
		}
	}

	return true;
}