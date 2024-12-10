#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

BulletManager* BulletManager::instance = nullptr;

struct Niveau 
{
    sf::Color couleur;
    sf::Vector2f position;
};

struct BoutonMenu
{
    sf::Color couleurmenu;
    sf::Vector2f positionmenu;
};


int main()
{

    std::vector <BoutonMenu> Press =
    {
        { sf::Color::Blue, {800,375} },
        { sf::Color::Magenta, {800,475} },
        { sf::Color::Yellow, {800,575} },
    };

    std::vector <sf::RectangleShape> StructMenu;
    for (const auto& BoutonMenu : Press)
    {
            sf::RectangleShape test2(sf::Vector2f(250, 75));
            test2.setFillColor(BoutonMenu.couleurmenu);
            test2.setPosition(BoutonMenu.positionmenu);
            StructMenu.push_back(test2);
    }



    std::vector <Niveau> niveaux =
    {
        { sf::Color::Cyan, {300, 400} },
        { sf::Color::Green, {600, 100} },
        { sf::Color::Blue, {750, 600} },
        { sf::Color::Yellow, {1050, 350} },
        { sf::Color::White, {1300, 800} },
        { sf::Color::Red, {1700, 500} },

    };

    std::vector<sf::CircleShape> lvls;
    for (const auto& Niveau : niveaux)
    {
        sf::CircleShape lvl(40);
        lvl.setFillColor(Niveau.couleur);
        lvl.setPosition(Niveau.position);
        lvls.push_back(lvl);
    }



    sf::RenderWindow menu(sf::VideoMode(1900, 1080), "Menu : Save The Moon");
    menu.setFramerateLimit(60);

    sf::Event event;


    menu.setVisible(true);

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
                        menu.setVisible(false);

                        //Selection des niveaux
                        sf::RenderWindow LvlSelect(sf::VideoMode(1900, 1080), "Selection Niveaux");
                        LvlSelect.setFramerateLimit(60);

                        LvlSelect.setVisible(true);

                        sf::RectangleShape BackLvl(sf::Vector2f(20, 20));
                        BackLvl.setFillColor(sf::Color::White);
                        
                        sf::Event event;

                        for (const auto& lvl : lvls)
                        {
                            LvlSelect.draw(lvl);
                        }

                        LvlSelect.draw(BackLvl);

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
                                            LvlSelect.setVisible(false);


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

                                    if (mouse1.x >= 0 && mouse1.x <= 20)
                                    {
                                        if (mouse1.y >= 0 && mouse1.y <= 20)
                                        {
                                            LvlSelect.close();
                                            menu.setVisible(true);

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }


            //Bouton Option
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 800 && mouse.x <= 1050)
                {
                    if (mouse.y >= 475 && mouse.y <= 550)
                    {
                        menu.setVisible(false);

                        //Selection des niveaux
                        sf::RenderWindow Option(sf::VideoMode(1900, 1080), "Option");
                        Option.setFramerateLimit(60);

                        sf::RectangleShape Back(sf::Vector2f(20, 20));

                        sf::Event event;

                        while (Option.isOpen())
                        {
                            sf::Vector2i mouse3 = sf::Mouse::getPosition(Option);

                            while (Option.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    Option.close();
                                }

                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                    if (mouse3.x >= 0 && mouse3.x <= 20)
                                    {
                                        if (mouse3.y >= 0 && mouse3.y <= 20)
                                        {
                                            Option.close();
                                            menu.setVisible(true);
                                        }
                                    }
                                }

                            }
                            Option.draw(Back);
                            Option.display();
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
        for (const auto& test2 : StructMenu)
        {
            menu.draw(test2);
        }
        menu.display();
    }
return 0;
}