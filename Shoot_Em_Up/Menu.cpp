#include "Menu.h"
#include "Music.h"
#include <iostream>

Button::Button(sf::Vector2f position_, ButtonId id_, sf::Color color_, sf::RectangleShape hitbox_, sf::Vector2f textureCoords_)
{
	this->position = position_;
	this->id = id_;
	this->color = color_;
	this->hitbox = hitbox_;
	this->hitbox.setOrigin({ this->hitbox.getSize().x / 2.f, this->hitbox.getSize().y / 2.f });
	this->hitbox.setPosition(this->position);
	this->hitbox.setFillColor(this->color);
	this->sprite = nullptr;
	this->textureCoords = textureCoords_;
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
	this->sprite = nullptr;
	this->textureCoords = { 0, 0 };
}

Button::~Button() {};

MenuManager::MenuManager()
{
	smallButtons = { BACK, MUTE, DEMUTE, VOLUMEUP, VOLUMEDOWN };

	background = new sf::Sprite;
	//background->setPosition({ WindowConfig::getInstance()->SIZE_X / 2.f, WindowConfig::getInstance()->SIZE_Y / 2.f });

	if (!loadTexture()) { std::cout << "Buttons texture failed\n"; }
	openMenu();
}

void MenuManager::openMenu()
{
	this->buttons.clear();

	addBackground(menuTexture);

	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,375 }, PLAY, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(250, 75))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,475 }, SETTINGS, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(250, 75))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1920 / 2,575 }, QUIT, sf::Color::Yellow, sf::RectangleShape(sf::Vector2f(250, 75))));

	setSprites();
}

void MenuManager::openOption()
{
	this->buttons.clear();

	addBackground(optionsTexture);
	
	this->buttons.push_back(new Button(sf::Vector2f{ 25,30 }, BACK, sf::Color::White, sf::RectangleShape(sf::Vector2f(30, 30)), { 0, 2 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 150,150 }, MUTE, sf::Color::Red, sf::RectangleShape(sf::Vector2f(30, 30)), { 2, 1 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 300,150 }, DEMUTE, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(30, 30)), { 2, 0 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 450,150 }, VOLUMEDOWN, sf::Color::Green, sf::RectangleShape(sf::Vector2f(30, 30)), { 0, 1 }));
	this->buttons.push_back(new Button(sf::Vector2f{ 600,150 }, VOLUMEUP, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(30, 30)), { 0, 0 }));

	setSprites();
}



void MenuManager::openLvlSelect()
{
	this->buttons.clear();

	addBackground(levelsSelectTexture);

	this->buttons.push_back(new Button(sf::Vector2f{ 25,30 }, BACK, sf::Color::White, sf::RectangleShape(sf::Vector2f(30, 30))));
	this->buttons.push_back(new Button(sf::Vector2f{ 300,400 }, LVL1, sf::Color::White, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 600,100 }, LVL2, sf::Color::Red, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 750,600 }, LVL3, sf::Color::Blue, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1050,350 }, LVL4, sf::Color::Green, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1300,800 }, LVL5, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(80, 80))));
	this->buttons.push_back(new Button(sf::Vector2f{ 1700,500 }, LVL6, sf::Color::Magenta, sf::RectangleShape(sf::Vector2f(80, 80))));

	setSprites();
}

void MenuManager::openCredits()
{
	this->buttons.clear();

	addBackground(menuTexture);

	setSprites();
}

void MenuManager::addBackground(sf::Texture &texture)
{
	background = new sf::Sprite;
	background->setTexture(texture);

	sf::FloatRect bounds = background->getLocalBounds();
	sf::Vector2u textureSize = background->getTexture()->getSize();
	background->setScale(
		float(WindowConfig::getInstance()->SIZE_X) / textureSize.x,
		float(WindowConfig::getInstance()->SIZE_Y) / textureSize.y
	);

	background->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	background->setPosition(WindowConfig::getInstance()->SIZE_X / 2.f, WindowConfig::getInstance()->SIZE_Y / 2.f);
}

void MenuManager::drawButtons(sf::RenderWindow& window)
{
	if (background)
	{
		window.draw(*background);
	}

	for (Button* button : this->buttons)
	{
		if (button->getSprite() == nullptr) { window.draw(button->getHitbox()); continue; }
		button->getSprite()->setPosition(button->getPosition());
		window.draw(*button->getSprite());
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

bool MenuManager::loadTexture()
{
	if (!this->smallButtonsTexture.loadFromFile("assets/textures/SmallButtons.png")) return false;
	if (!this->menuTexture.loadFromFile("assets/textures/OptionsBackground.png")) return false;
	if (!this->optionsTexture.loadFromFile("assets/textures/OptionsBackground.png")) return false;
	if (!this->levelsSelectTexture.loadFromFile("assets/textures/SpaceBackground.png")) return false;
	this->setSprites();
	return true;
}

void MenuManager::setSprites()
{
	for (Button* adress : this->buttons)
	{
		if (adress->getSprite() != nullptr) continue;

		sf::Sprite* sprite = nullptr;

		for (ButtonId id : this->smallButtons)
		{
			if (adress->getId() == id)
			{
				sprite = new sf::Sprite;
				sprite->setTexture(this->smallButtonsTexture);
			}
		}
		if (sprite == nullptr) continue;

		sprite->setScale({ smallButtonsTexture.getSize().x / adress->getHitbox().getSize().x / 2.5f, smallButtonsTexture.getSize().y / adress->getHitbox().getSize().y / 2.5f });
		sprite->setOrigin({
			adress->getHitbox().getOrigin().y / sprite->getScale().y,
			adress->getHitbox().getOrigin().y / sprite->getScale().y
			});

		sprite->setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * 25,
			adress->getTextureCoords().y * 30,
			25,
			30));

		adress->setSprite(sprite);
	}
}



