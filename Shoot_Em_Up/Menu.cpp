#include "Menu.h"
#include "Music.h"
#include <iostream>


MenuManager::MenuManager()
{
	openMenu();
}

void MenuManager::openMenu()
{
	this->buttons.clear();

	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,375 }, PLAY, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(250, 75))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,475 }, SETTINGS, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(250, 75))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,575 }, QUIT, sf::Color::Yellow, sf::RectangleShape(sf::Vector2f(250, 75))));

}

void MenuManager::openOption()
{
	this->buttons.clear();

	this->buttons.push_back(new Button(sf::Vector2f{ 0,0 }, BACK, sf::Color::White, sf::RectangleShape(sf::Vector2f(30,30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 150,150 }, MUTE, sf::Color::Red, sf::RectangleShape(sf::Vector2f(30, 30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 300,150 }, DEMUTE, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(30, 30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 450,150 }, VOLUMEDOWN, sf::Color::Green, sf::RectangleShape(sf::Vector2f(30, 30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 600,150 }, VOLUMEUP, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(30, 30))));

}

void MenuManager::openLvlSelect()
{
	this->buttons.clear();

	this->buttons.push_back(new Button(sf::Vector2f{ 0,0 }, BACK, sf::Color::White, sf::RectangleShape(sf::Vector2f(30, 30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 300,400 }, LVL1, sf::Color::White, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 600,100 }, LVL2, sf::Color::Red, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 750,600 }, LVL3, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1050,350 }, LVL4, sf::Color::Green, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1300,800 }, LVL5, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1700,500 }, LVL6, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(80, 80))));
}

void MenuManager::openCredits()
{
	this->buttons.clear();

}

void MenuManager::drawButtons(sf::RenderWindow& window)
{
	for (Button* button : this->buttons)
	{
		window.draw(button->getHitbox());
	}
}

void MenuManager::activateButton(ButtonId id)
{
	switch (id)
	{
	case NOTHING: break;
	case PLAY: openLvlSelect(); break;
	case SETTINGS: openOption(); break;
	case QUIT: break;
	case BACK: openMenu(); break;
	case MUTE: Music::getInstance()->mute(); break;
	case DEMUTE: Music::getInstance()->demute(); break;
	case VOLUMEUP: Music::getInstance()->UPVolume(); break;
	case VOLUMEDOWN:Music::getInstance()->DOWNVolume(); break;

	}
}

ButtonId MenuManager::isMouseOnButton(sf::Vector2i mousePosition)
{
	for (Button* button: this->buttons)
	{
		if (button->getHitbox().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			//std::cout << "Button clicked\n";
			return button->getId();
		}
	}
	return NOTHING;
}



Button::Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_, sf::Sprite sprite_)
{
	this->position = position_;
	this->id = id_;
	this->color = color_;
	this->hitbox = hitbox_;
	this->hitbox.setOrigin({ this->hitbox.getSize().x / 2.f, this->hitbox.getSize().y / 2.f });
	this->hitbox.setPosition(this->position);
	this->hitbox.setFillColor(this->color);
	this->sprite = sprite_;
}

Button::Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_)
{
	this->position = position_;
	this->id = id_;
	this->color = color_;
	this->hitbox = hitbox_;
	this->hitbox.setOrigin({ this->hitbox.getSize().x / 2.f, this->hitbox.getSize().y / 2.f });
	this->hitbox.setPosition(this->position);
	this->hitbox.setFillColor(this->color);
	//this->sprite = ;
}



