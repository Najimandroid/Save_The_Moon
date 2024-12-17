#include "Background.h"
#include "Level.h"

Background::Background(std::vector<sf::Texture> textures_)
{
	layers.resize(textures_.size());
	for (int i = 0; i < textures_.size(); i++)
	{
		Layer* layer_n1 = new Layer(textures_[i], 0.f);
		Layer* layer_n2 = new Layer(textures_[i], 1.f);
		layers[i].push_back(layer_n1);
		layers[i].push_back(layer_n2);
	}
}

void Background::drawBackground(sf::RenderWindow& window)
{
	for (std::vector<Layer*> list : this->layers)
	{
		for (int i = 0; i < list.size(); i++)
		{
			sf::Sprite body;
			body.setScale({ (float)window.getSize().x / list[i]->getTexture().getSize().x, (float)window.getSize().y / list[i]->getTexture().getSize().y });
			body.setTexture(list[i]->getTexture());
			body.setOrigin({ list[i]->getTexture().getSize().x / 2.f, list[i]->getTexture().getSize().y / 2.f });
			body.setPosition(list[i]->getPosition());

			window.draw(body);
		}
	}
}

void Background::moveBackground(float deltaTime)
{
	int count = 0;
	for (std::vector<Layer*> list : this->layers)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i]->getPosition().x <= 
				(list[i]->getTexture().getSize().x / 2) * -1.f * WindowConfig::getInstance()->SIZE_X / list[i]->getTexture().getSize().x) //checks if layer if out of bounds
			{
				list[i]->setPosition({ (WindowConfig::getInstance()->SIZE_X / 2.f) + (WindowConfig::getInstance()->SIZE_X), WindowConfig::getInstance()->SIZE_Y / 2.f });
			}
			else
			{
				sf::Vector2f velocity = { -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime / (list.size() - count + 2), 0 };
				list[i]->setPosition(list[i]->getPosition() + velocity);
			}
		}
		count++;
	}
}