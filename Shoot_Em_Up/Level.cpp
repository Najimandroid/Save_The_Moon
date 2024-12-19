#include "Wall.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Level.h"
#include "Music.h"
#include "Background.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <string>

unsigned int LevelManager::colorToInt(const sf::Color& color)
{
	return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

bool LevelManager::unloadLevel()
{
	EnemyManager::getInstance()->getEnemies().clear();
	WallManager::getInstance()->getWalls().clear();
	BulletManager::getInstance()->getBullets().clear();

	currentBackground->getLayers().clear();

	PlayerManager::getInstance()->getPlayers().clear();

	return true;
}

bool LevelManager::loadLevel(int levelIndex)
{
	
	if (!this->levelImage.loadFromFile("assets/levels/Level_" + std::to_string(levelIndex) + "/body.png"))  //this->levels.at(size_t(levelIndex))
	{
		std::cout << "FAILED LOADING LEVEL: " << levelIndex << '\n';
		return false;
	}

	Music::getInstance()->SetSound("assets/musics/Level_" + std::to_string(levelIndex) + ".wav");

	sf::Texture layer1, layer2, layer3;
	layer1.loadFromFile("assets/backgrounds/Level_" + std::to_string(levelIndex) + "/Layer1.png"); layer2.loadFromFile("assets/backgrounds/Level_" + std::to_string(levelIndex) + "/Layer2.png"); layer3.loadFromFile("assets/backgrounds/Level_" + std::to_string(levelIndex) + "/Layer3.png");
	std::vector<sf::Texture> textures_ =
	{
		layer1,
		layer2,
		layer3,
	};

	this->currentBackground = new Background(textures_);

	WallManager* wallManager = WallManager::getInstance();
	EnemyManager* enemyManager = EnemyManager::getInstance();
	CollectableManager* collectableManager = CollectableManager::getInstance();

	for (int x = 0; x < this->levelImage.getSize().x; x++)
	{
		for (int y = 0; y < this->levelImage.getSize().y; y++)
		{
			sf::Vector2f SPAWN_POSITION = { TILE_SIZE * float(x), TILE_SIZE * float(y) + TILE_SIZE / 2 };

			sf::Color color = this->levelImage.getPixel(x, y);
			unsigned int colorCode = colorToInt(color);

			switch (colorCode)
			{
			case 0x000000FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 0, (float)levelIndex -1}); break; //whole wall
			case 0x737373FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 5, (float)levelIndex -1}); break; //grid
			case 0x353535FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 1, (float)levelIndex -1}); break; //up grid
			case 0x3a2d2dFF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 2, (float)levelIndex -1}); break; //down grid
			case 0x522a2aFF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 3, (float)levelIndex -1}); break; //left grid
			case 0x561717FF: wallManager->spawnWall(SPAWN_POSITION, { TILE_SIZE , TILE_SIZE })->setTextureCoords({ 4, (float)levelIndex -1}); break; //right grid

			case 0xFFFF00FF: collectableManager->spawnCollectable(SPAWN_POSITION, CollectableType::COIN); break; //coin
			case 0xFF0000FF: collectableManager->spawnCollectable(SPAWN_POSITION, CollectableType::HEART); break; //heart

			case 0x59fb80FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::DEFAULT); break; //default
			case 0xd759fbFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SNIPER); break; //sniper
			case 0xdbde1aFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::MOUTH); break; //mouth
			case 0x5f75ffFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::WHEEL); break; //wheel
			case 0xfb6a6aFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::WAVE); break; //wave
			case 0xfbbb1eFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::HOMING); break; //homing

			case 0xff905fFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::BOSS_1); break; //giga mouth

			case 0xb93729FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::SPIKE); break; //spike

			case 0x1000e2FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::TURRET_UP); break; //turret up
			case 0xc8c4fbFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::TURRET_DOWN); break; //turret down
			case 0x08006fFF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::TURRET_LEFT); break; //turret left
			case 0x867fe2FF: enemyManager->spawnEnemy(SPAWN_POSITION, EnemyType::TURRET_RIGHT); break; //turret right
			}
		}
	}

	return true;
}