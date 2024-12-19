#pragma once

#include "Player.h"
#include "Music.h"
#include "Menu.h"
#include "HealthBar.h"
#include "Level.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Window.h"
#include "Bullet.h"
#include "CustomBullets.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>   
#include <cmath>
#include <functional>
#include <chrono>
#include <iostream>


class Game
{
private:
	bool gameStarted;
	int currentLevel;

	sf::Font* font;
	sf::Text* scoreText;

	bool isPaused;

	float deltaTime;

	sf::Clock clock;
	sf::Event event;
public:
	Game();

	void initSeed();

	MenuManager* createMenu(sf::RenderWindow& window);

	void startLevel(int levelIndex_);

	void Gameloop(sf::RenderWindow& window, MenuManager* menuManager);

	void checkGameCollisions();
	void updateGameObjects(float deltaTime_);
	void drawGameObjects(sf::RenderWindow& window);
};