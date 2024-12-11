#pragma once
#include "Wall.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//=> Tile size : 60px * 60px

class LevelManager 
{
private:
	static LevelManager* instance;

	sf::Image levelImage;

	std::vector<std::string> levels =
	{
		"assets/levels/TestLevel.png",
	};

	LevelManager() {};
public:
	float TILE_SIZE = 60;
	float SCROLLING_SPEED = 100;

	static LevelManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new LevelManager();
		}
		return instance;
	}

	bool loadLevel(int levelIndex);
};