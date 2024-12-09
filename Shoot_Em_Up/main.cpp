#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

BulletManager* BulletManager::instance = nullptr;

int main()
{

    sf::RenderWindow menu(sf::VideoMode(1900, 1080), "Save The Moon");
    menu.setFramerateLimit(60);


    sf::RectangleShape Bouton(sf::Vector2f(50, 50));
    Bouton.setFillColor(sf::Color(0, 255, 0, 255));
    Bouton.setOutlineColor(sf::Color::Blue);

    sf::Event event;

    while (menu.isOpen())
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(menu);

        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menu.close();
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 0 && mouse.x <= 100)
                {
                    if (mouse.y >= 0 && mouse.y <= 100)
                    {
                        menu.close();

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
                                sf::RectangleShape boule(sf::Vector2f(5, 5));
                                boule.setFillColor(sf::Color::White);
                                boule.setPosition(adress->getPosition());
                                window.draw(boule);
                            }

                            deltaTime = clock.restart().asSeconds();
                            player.shootCheck();

                            for (Bullet* adress : bulletManager->balles)
                            {
                                bulletManager->movebullet(deltaTime, adress);
                                std::cout << "[ " << adress << ", ";
                            } std::cout << " ]" << std::endl;
                            bulletManager->despawnbullet();
                            player.updatePosition(deltaTime);

                            ship.setPosition(player.getPosition());

                            window.draw(ship);
                            window.display();
                        }
                    }
                }
            }
        }
        menu.clear();
        menu.draw(Bouton);
        menu.display();
    }
return 0;
}