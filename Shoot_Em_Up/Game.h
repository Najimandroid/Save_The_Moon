#pragma once

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>


class Game
{
public:
	MenuManager* createMenu(sf::RenderWindow& window);
	void Gameloop();
};