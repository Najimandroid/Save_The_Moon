#pragma once
#include "Wall.h"
#include "Window.h"
#include "Background.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//=> Tile size : 60px * 60px

class LevelManager 
{
private:
	static LevelManager* instance;

	sf::Image levelImage;

	Background* currentBackground;

	std::vector<std::string> levels =
	{
		"assets/levels/TestLevel.png",
	};

	LevelManager() { currentBackground = nullptr; };
public:
	float TILE_SIZE = WindowConfig::getInstance()->SIZE_Y / 18.f;
	float SCROLLING_SPEED = WindowConfig::getInstance()->SIZE_X/ 12.8f;

	static LevelManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new LevelManager();
		}
		return instance;
	}

	Background* getBackground() { return currentBackground; }

	bool loadLevel(int levelIndex);
};