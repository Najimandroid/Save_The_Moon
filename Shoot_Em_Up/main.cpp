#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

BulletManager* BulletManager::instance = nullptr;


int Long = 1900;
int Larg = 1080;

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

struct BoutonSon
{
    sf::Color CouleurSon;
    sf::Vector2f PositionSon;
};

struct LvlAvailable
{
    bool Lvl2 = false;
    bool Lvl3 = true; 
    bool Lvl4 = false;
    bool Lvl5 = false;
    bool Lvl6 = false;
};

struct Upgrade
{
    sf::Color colorupgrade;
    sf::Vector2f positionupgrade;
};




bool music = true;


int main()
{
    struct LvlAvailable Dispo;


    sf::SoundBuffer MusicMenu;

    if (!MusicMenu.loadFromFile("TitleScreen.wav")) {
        std::cout << "Erreur : Impossible de charger le fichier audio." << std::endl;
        return -1;
    }


    sf::Sound MusicProc;
    MusicProc.setBuffer(MusicMenu);
    if (music == true)
    {
        MusicProc.play();
    }

    MusicProc.setLoop(true);

    if (music == false)
    {
        MusicProc.stop();
       MusicProc.setVolume(0);
    }



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


    std::vector <BoutonSon> Sound =
    {
        { sf::Color::White,{0,0} },
        { sf::Color::Red, {150,150} },
        { sf::Color::Blue, {300,150} },
    };

    std::vector <sf::RectangleShape> StructSon;
    for (const auto& BoutonSon : Sound)
    {
        sf::RectangleShape SoundB(sf::Vector2f(30, 30));
        SoundB.setFillColor(BoutonSon.CouleurSon);
        SoundB.setPosition(BoutonSon.PositionSon);
        StructSon.push_back(SoundB);
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

    std::vector <Upgrade> UP =
    {
        {sf::Color::Blue, {300,500} },
        {sf::Color::Red, {600,500} },
        {sf::Color::Green, {900,500} },
    };

    std::vector <sf::CircleShape> UPG;
    for (const auto& Upgrade : UP)
    {
        sf::CircleShape BUP(10);
        BUP.setFillColor(Upgrade.colorupgrade);
        BUP.setPosition(Upgrade.positionupgrade);
        UPG.push_back(BUP);
    }


    //test bouton résolution
    sf::RectangleShape taille(sf::Vector2f(50, 50));
    taille.setFillColor(sf::Color::White);
    taille.setPosition(sf::Vector2f(150, 150));



    sf::RenderWindow menu(sf::VideoMode(Long, Larg), "Menu : Save The Moon");
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


            //Résolution fenetre
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 150 && mouse.x <= 200)
                {
                    if (mouse.y >= 150 && mouse.y <= 200)
                    {
                        menu.setSize(sf::Vector2u(1024, 768));
                    }
                }
            }

            //Bouton Menu Selection Niveau
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (mouse.x >= 800 && mouse.x <= 1050)
                {
                    if (mouse.y >= 375 && mouse.y <= 450)
                    {
                        menu.setVisible(false);
                        MusicProc.stop();


                        sf::SoundBuffer MusicSelect;

                        if (!MusicSelect.loadFromFile("SelectLvl.wav")) {
                            return -1;
                        }


                        sf::Sound MusicNiv;
                        MusicNiv.setBuffer(MusicSelect);
                        MusicNiv.play();
                        if (music == false)
                        {
                            MusicNiv.setVolume(0);
                        }

                        MusicNiv.setLoop(true);

                        //Selection des niveaux
                        sf::RenderWindow LvlSelect(sf::VideoMode(1900, 1080), "Selection Niveaux");
                        LvlSelect.setFramerateLimit(60);

                        LvlSelect.setVisible(true);

                        sf::RectangleShape BackLvl(sf::Vector2f(20, 20));
                        BackLvl.setFillColor(sf::Color::White);

                        sf::RectangleShape ShopBouton(sf::Vector2f(150,50));
                        ShopBouton.setFillColor(sf::Color::Magenta);
                        ShopBouton.setPosition(sf::Vector2f(1700, 10));

                        
                        sf::Event event;

                        for (const auto& lvl : lvls)
                        {
                            LvlSelect.draw(lvl);
                        }

                        LvlSelect.draw(BackLvl);
                        LvlSelect.draw(ShopBouton);

                        LvlSelect.display();

                        //Menu Selection Lvl
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

                                    if (mouse1.x >= 1700 && mouse1.x <= 1850)
                                    {
                                        if (mouse1.y >= 10 && mouse1.y <= 60)
                                        {
                                            LvlSelect.setVisible(false);
                                            MusicNiv.stop();

                                            sf::RenderWindow Boutique(sf::VideoMode(1900, 1080), "Boutique");
                                            Boutique.setFramerateLimit(60);

                                            Boutique.setVisible(true);

                                            sf::Event event;
                                            while (Boutique.isOpen())
                                            {
                                                sf::Vector2i mouseBoutique = sf::Mouse::getPosition(Boutique);

                                                while (Boutique.pollEvent(event))
                                                {
                                                    if (event.type == sf::Event::Closed)
                                                    {
                                                        Boutique.close();
                                                    }
                                                }

                                                for (const auto& BUP : UPG)
                                                {
                                                    Boutique.draw(BUP);
                                                }
                                                Boutique.display();
                                            }
                                        }
                                    }


                                    //Niveaux1
                                    if (mouse1.x >= 300 && mouse1.x <= 380)
                                    {
                                        if (mouse1.y >= 400 && mouse1.y <= 480)
                                        {
                                            LvlSelect.setVisible(false);
                                            MusicNiv.stop();


                                            sf::SoundBuffer Niv1;

                                            if (!Niv1.loadFromFile("Niv1.wav")) {
                                                return -1;
                                            }

                                            sf::Sound Lvl1;
                                            Lvl1.setBuffer(Niv1);
                                            Lvl1.play();
                                            if (music == false)
                                            {
                                                Lvl1.setVolume(0);
                                            }

                                            Lvl1.setLoop(true);

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
                                                }

                                                bulletManager->despawnbullet();
                                                player.updatePosition(deltaTime);

                                                ship.setPosition(player.getPosition());

                                                game.draw(ship);
                                                game.display();
                                            }
                                        }
                                    }


                                    //Niveaux 2
                                    if (mouse1.x >= 600 && mouse1.x <= 680)
                                    {
                                        if (mouse1.y >= 100 && mouse1.y <= 180 && Dispo.Lvl2 == true)
                                        {
                                            LvlSelect.setVisible(false);
                                        }
                                    }


                                    //Niveaux 3
                                    if (mouse1.x >= 750 && mouse1.x <= 830)
                                    {
                                        if (mouse1.y >= 600 && mouse1.y <= 680 && Dispo.Lvl3 == true)
                                        {
                                            Dispo.Lvl2 = true;
                                        }
                                    }


                                    //Niveaux 4
                                    if (mouse1.x >= 1050 && mouse1.x <= 1130)
                                    {
                                        if (mouse1.y >= 350 && mouse1.y <= 430 && Dispo.Lvl4 == true)
                                        {
                                            LvlSelect.setVisible(false);
                                        }
                                    }


                                    //Niveaux 5
                                    if (mouse1.x >= 1300 && mouse1.x <= 1380)
                                    {
                                        if (mouse1.y >= 800 && mouse1.y <= 880 && Dispo.Lvl5 == true)
                                        {
                                            LvlSelect.setVisible(false);
                                        }
                                    }


                                    //Niveaux 6
                                    if (mouse1.x >= 1700 && mouse1.x <= 1780)
                                    {
                                        if (mouse1.y >= 500 && mouse1.y <= 580 && Dispo.Lvl6 == true)
                                        {
                                            LvlSelect.setVisible(false);
                                        }
                                    }

                                    //Back to menu
                                    if (mouse1.x >= 0 && mouse1.x <= 20)
                                    {
                                        if (mouse1.y >= 0 && mouse1.y <= 20)
                                        {
                                            LvlSelect.close();
                                            menu.setVisible(true);
                                            if (music == true)
                                            {
                                                MusicProc.play();
                                            }
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
                        MusicProc.stop();

                        //Menu Option
                        sf::RenderWindow Option(sf::VideoMode(1900, 1080), "Option");
                        Option.setFramerateLimit(60);



                        sf::SoundBuffer MusicOption;

                        

                        if (!MusicOption.loadFromFile("Option.wav")) {
                            return -1;
                        }

                        sf::Sound MusicOp;
                        MusicOp.setBuffer(MusicOption);
                        MusicOp.play();

                        if (music == false)
                        {
                            MusicOp.setVolume(0);
                        }
                        
                        MusicOp.setLoop(true);

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
                                            if (music == true)
                                            {
                                                MusicProc.play();
                                            }
                                        }
                                    }

                                    if (mouse3.x >= 150 && mouse3.x <= 180)
                                    {
                                        if (mouse3.y >= 150 && mouse3.y <= 180)
                                        {
                                            MusicOp.stop();
                                            music = false;
                                        }
                                    }

                                    if (mouse3.x >= 300 && mouse3.x <= 330)
                                    {
                                        if (mouse3.y >= 150 && mouse3.y <= 180)
                                        {
                                            music = true;
                                            MusicOp.play();

                                        }
                                    }
                                }


                            }
                            for (auto& SoundB : StructSon)
                            {
                                Option.draw(SoundB);
                            }
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
        menu.draw(taille);
        menu.display();

    }
return 0;
}
