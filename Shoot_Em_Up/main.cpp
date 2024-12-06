#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

int main()
{
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    //creation d'un objet joueur
    Player player(100, { 1900 / 3, 1080 / 2 });
    
    //creation d'un enemie
    Enemy alien(100, 50, { 1900, 1080 / 2 }, 10);

    //creation d'une horloge
    sf::Clock clock;
    float deltaTime;
    

    sf::RectangleShape ship(sf::Vector2f(100, 100));
    ship.setFillColor(sf::Color::Green);

    ship.setOrigin(sf::Vector2f{ ship.getSize().x, ship.getSize().y } / 2.f);
    ship.setPosition(player.getPosition());

    sf::RectangleShape alienShip(sf::Vector2f(75, 75));
    alienShip.setFillColor(sf::Color::Red);

    alienShip.setOrigin(sf::Vector2f{ alienShip.getSize().x, alienShip.getSize().y } / 2.f);
    alienShip.setPosition(alien.getPosition());

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

        deltaTime = clock.restart().asSeconds();
        player.updatePosition(deltaTime);
        alien.updatePosition(deltaTime);

        ship.setPosition(player.getPosition());
        alienShip.setPosition(alien.getPosition());

        window.draw(ship);
        window.draw(alienShip);
        window.display();
    }


return 0;
}