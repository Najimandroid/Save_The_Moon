#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include <vector>
#include "Music.h"

enum ButtonId
{
	NOTHING, PLAY,SETTINGS,QUIT,BACK,MUTE,DEMUTE,VOLUMEUP,VOLUMEDOWN,LVL1,LVL2,LVL3,LVL4,LVL5,LVL6

};

class Button
{
private:
	sf::Vector2f position;
	ButtonId id;
	sf::Color color;
	sf::RectangleShape hitbox;

	sf::Vector2f textureCoords;
	sf::Sprite* sprite;


public:
	Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_, sf::Vector2f textureCoords_);
	Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_);

	virtual ~Button();

	sf::Sprite* getSprite() const { if (sprite) { return sprite; } return nullptr; }
	ButtonId getId() const { return id; }
	sf::Vector2f getPosition() const { return position; }
	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Vector2f getTextureCoords() const { return textureCoords; }

	void setSprite(sf::Sprite* newSprite) { sprite = newSprite; }
	void setTextureCoords(sf::Vector2f newCoords) { sprite = nullptr; textureCoords = newCoords; }
};

class MenuManager
{
private:
	std::vector <Button*> buttons;
	sf::Sprite* background;

	sf::Texture smallButtonsTexture;
	sf::Texture bigButtonsTexture;

	sf::Texture menuTexture;
	sf::Texture optionsTexture;
	sf::Texture levelsSelectTexture;

	std::vector<ButtonId> smallButtons;
public:
	MenuManager();

	bool loadTexture();
	void setSprites();
	
	void addBackground(sf::Texture &texture);
	void openMenu();
	void openOption();
	void openLvlSelect();
	void openCredits();
	void drawButtons(sf::RenderWindow& window);
	void activateButton(ButtonId id);
	ButtonId isMouseOnButton(sf::Vector2i mousePosition);
};

