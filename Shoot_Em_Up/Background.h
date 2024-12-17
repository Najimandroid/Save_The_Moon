#pragma once
#include "Window.h"
#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Layer
{
private:
	sf::Vector2f position;
	sf::Texture texture;
public:
	Layer(sf::Texture texture_, float offset_) :
		position({ (WindowConfig::getInstance()->SIZE_X / 2.f) + (WindowConfig::getInstance()->SIZE_X * offset_), WindowConfig::getInstance()->SIZE_Y / 2.f }),
		texture(texture_)
	{}

	sf::Texture& getTexture() { return texture; }
	sf::Vector2f getPosition() { return position; }

	void setPosition(sf::Vector2f newPosition) { position = newPosition; }
};

class Background 
{
private: 
	std::vector<std::vector<Layer*>> layers;
public:
	Background(std::vector<sf::Texture> textures_);

	void drawBackground(sf::RenderWindow& window);
	void moveBackground(float deltaTime);
};