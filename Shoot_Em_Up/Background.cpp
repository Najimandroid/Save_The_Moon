#include "Background.h"
#include "Window.h"
#include "Level.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void Background::drawBackground(sf::RenderWindow& window)
{
	for (Layer* layer : this->layers)
	{
		sf::Sprite body;
		body.setScale({ (float)window.getSize().x / layer->getTexture().getSize().x, (float)window.getSize().y / layer->getTexture().getSize().y });
		body.setTexture(layer->getTexture());
		body.setOrigin({ layer->getTexture().getSize().x / 2.f, layer->getTexture().getSize().y / 2.f });
		body.setPosition(layer->getPosition());

		window.draw(body);
	}
}

void Background::moveBackground(float deltaTime)
{
	for (int i = 0; i < this->layers.size(); i++)
	{
		sf::Vector2f velocity = { -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime / (this->layers.size() - i+1), 0};
		layers[i]->setPosition(layers[i]->getPosition() + velocity);
	}
}