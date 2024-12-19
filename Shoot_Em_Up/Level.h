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

	std::vector<int> completion;

	LevelManager() { currentBackground = nullptr;
	completion = { 0, 0, 0, 0, 0, 0 };
	};
public:
	float TILE_SIZE = WindowConfig::getInstance()->SIZE_Y / 18.f;
	float SCROLLING_SPEED = WindowConfig::getInstance()->SIZE_X/ 11.f;

	static LevelManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new LevelManager();
		}
		return instance;
	}

	Background* getBackground() { return currentBackground; }

	std::vector<int> getCompletion() { return completion; }
	void completed(int levelIndex) { completion[levelIndex] = 1; }

	bool loadLevel(int levelIndex);
	bool unloadLevel();

	unsigned int colorToInt(const sf::Color& color);
};