#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Music.h"

enum ButtonId
{
	NOTHING, PLAY,SETTINGS,QUIT,BACK,MUTE,DEMUTE,VOLUMEUP,VOLUMEDOWN,LVL1,LVL2,LVL3,LVL4,LVL5,LVL6

};

class Button
{
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	ButtonId id;
	sf::Color color;
	sf::RectangleShape hitbox;

public:
	Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_, sf::Sprite sprite_);
	Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_);

	ButtonId getId()
	{
		return id;
	}

	sf::Vector2f getPosition()
	{
		return position;
	}

	sf::RectangleShape& getHitbox()
	{
		return hitbox;
	}
};

class MenuManager
{
private:
	std::vector <Button*> buttons;
public:
	MenuManager();

	void openMenu();
	void openOption();
	void openLvlSelect();
	void openCredits();
	void drawButtons(sf::RenderWindow& window);
	void activateButton(ButtonId id);
	ButtonId isMouseOnButton(sf::Vector2i mousePosition);
};

