#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

BulletManager* BulletManager::instance = nullptr;

int main()
{
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon");
    window.setFramerateLimit(60);

    BulletManager* bulletManager = BulletManager::getInstance();

    //test
    //creation d'un objet joueur
    Player player(100, { 1900 / 2, 1080 / 2 });

    //creation d'une horloge
    sf::Clock clock;
    float deltaTime;
    

    sf::RectangleShape ship(sf::Vector2f(100, 100));
    ship.setFillColor(sf::Color::Green);

    ship.setOrigin(sf::Vector2f{ ship.getSize().x, ship.getSize().y } / 2.f);
    ship.setPosition(player.getPosition());


    while (window.isOpen()) 
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close(); // Fermer avec Échap
            }
        }  

        for (Bullet* adress : bulletManager->balles)
        {
            sf::RectangleShape boule(sf::Vector2f(5,5));
            boule.setFillColor(sf::Color:: White);
            boule.setPosition(adress->getPosition());
            window.draw(boule);
        }

        deltaTime = clock.restart().asSeconds();
        player.shootCheck();

        for (Bullet* adress : bulletManager->balles)
        {
            bulletManager->movebullet(deltaTime, adress);
            
        }
        bulletManager->despawnbullet();
        player.updatePosition(deltaTime);

        ship.setPosition(player.getPosition());

        window.draw(ship);
        window.display();
    }


return 0;
}