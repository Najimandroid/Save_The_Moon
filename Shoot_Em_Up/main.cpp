#include "Player.h"
#include "Bullet.h"
#include "Music.h"
#include "Menu.h"
#include "Game.h"
#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

BulletManager* BulletManager::instance = nullptr;
Music* Music::instance = nullptr;

int Long = 1900;
int Larg = 1080;

struct LvlAvailable
{
    bool Lvl2 = false;
    bool Lvl3 = true; 
    bool Lvl4 = false;
    bool Lvl5 = false;
    bool Lvl6 = false;
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(Long, Larg), "Menu : Save The Moon");

    Game game;
    Music* change = Music::getInstance();
    MenuManager* menu = game.createMenu(window);
    struct LvlAvailable Dispo;
    change->SetSound("TitleScreen.wav");
    sf::Event event;

    while (window.isOpen())
    {
        window.clear();
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //Bouton Menu Selection Niveau
            if (event.type == sf::Event::MouseButtonPressed)
            {
                menu->activateButton(menu->isMouseOnButton(sf::Mouse::getPosition(window)));
            }
     
        }
        menu->drawButtons(window);
        window.display();
    }
return 0;
}
