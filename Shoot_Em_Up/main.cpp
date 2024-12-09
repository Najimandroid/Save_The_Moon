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


    sf::RectangleShape BoutonPlay(sf::Vector2f(250, 75));
    BoutonPlay.setPosition(800, 375);
    BoutonPlay.setFillColor(sf::Color::Blue);

    sf::RectangleShape BoutonOption(sf::Vector2f(250, 75));
    BoutonOption.setPosition(800, 475);
    BoutonOption.setFillColor(sf::Color::Magenta);

    sf::RectangleShape BoutonClose(sf::Vector2f(250, 75));
    BoutonClose.setPosition(800, 575);
    BoutonClose.setFillColor(sf::Color::Yellow);


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

            //Bouton Lancer Jeu
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 800 && mouse.x <= 1050)
                {
                    if (mouse.y >= 375 && mouse.y <= 450)
                    {
                        menu.close();

                        //Selection des niveaux
                        sf::RenderWindow LvlSelect(sf::VideoMode(1900, 1080), "Selection Niveaux");
                        LvlSelect.setFramerateLimit(60);

                        sf::CircleShape Niveaux1(40);
                        Niveaux1.setFillColor(sf::Color::Cyan);
                        Niveaux1.setPosition(300,400);


                        sf::CircleShape Niveaux2(40);
                        Niveaux2.setFillColor(sf::Color::Green);
                        Niveaux2.setPosition(600, 100);

                        sf::CircleShape Niveaux3(40);
                        Niveaux3.setFillColor(sf::Color::Blue);
                        Niveaux3.setPosition(750, 600);

                        sf::CircleShape Niveaux4(40);
                        Niveaux4.setFillColor(sf::Color::Yellow);
                        Niveaux4.setPosition(1050, 350);

                        sf::CircleShape Niveaux5(40);
                        Niveaux5.setFillColor(sf::Color::White);
                        Niveaux5.setPosition(1300, 800);

                        sf::CircleShape Niveaux6(40);
                        Niveaux6.setFillColor(sf::Color::Red);
                        Niveaux6.setPosition(1700, 500);

                        sf::Event event;

                        LvlSelect.clear();
                        LvlSelect.draw(Niveaux1);
                        LvlSelect.draw(Niveaux2);
                        LvlSelect.draw(Niveaux3);
                        LvlSelect.draw(Niveaux4);
                        LvlSelect.draw(Niveaux5);
                        LvlSelect.draw(Niveaux6);
                        LvlSelect.display();


                        while (LvlSelect.isOpen())
                        {
                            sf::Vector2i mouse1 = sf::Mouse::getPosition(LvlSelect);


                            while (LvlSelect.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    LvlSelect.close();
                                }

                                //Bouton Lancer Jeu
                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                    if (mouse1.x >= 300 && mouse1.x <= 350)
                                    {
                                        if (mouse1.y >= 400 && mouse1.y <= 450)
                                        {
                                            LvlSelect.close();


                                            //creation d'une fenetre
                                            sf::RenderWindow game(sf::VideoMode(1900, 1080), "Save The Moon");
                                            game.setFramerateLimit(60);

                                            BulletManager* bulletManager = BulletManager::getInstance();

                                            //creation d'un objet joueur
                                            Player player(100, { 1900 / 2, 1080 / 2 });

                                            //creation d'une horloge
                                            sf::Clock clock;
                                            float deltaTime;


                                            sf::RectangleShape ship(sf::Vector2f(100, 100));
                                            ship.setFillColor(sf::Color::Green);

                                            ship.setOrigin(sf::Vector2f{ ship.getSize().x, ship.getSize().y } / 2.f);
                                            ship.setPosition(player.getPosition());


                                            while (game.isOpen())
                                            {
                                                game.clear();

                                                sf::Event event;
                                                while (game.pollEvent(event))
                                                {
                                                    if (event.type == sf::Event::Closed)
                                                        game.close();

                                                    if (event.type == sf::Event::KeyPressed)
                                                    {
                                                        if (event.key.code == sf::Keyboard::Escape)
                                                            game.close(); // Fermer avec Échap
                                                    }
                                                }

                                                for (Bullet* adress : bulletManager->balles)
                                                {
                                                    sf::RectangleShape boule(sf::Vector2f(5, 5));
                                                    boule.setFillColor(sf::Color::White);
                                                    boule.setPosition(adress->getPosition());
                                                    game.draw(boule);
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

                                                game.draw(ship);
                                                game.display();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }                        
            //Bouton Close Menu
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 800 && mouse.x <= 1050)
                {
                    if (mouse.y >= 575 && mouse.y <= 650)
                    {
                        menu.close();
                    }
                }
            }
        }
        menu.clear();
        menu.draw(BoutonPlay);
        menu.draw(BoutonOption);
        menu.draw(BoutonClose);
        menu.display();
    }
return 0;
}