#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{

	sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::RectangleShape player(sf::Vector2f(200, 200));

    player.setFillColor(sf::Color::Red);

    player.setOrigin(sf::Vector2f{ player.getSize().x, player.getSize().y } / 2.f);
    player.setPosition(1900 / 2, 1080 / 2);


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


            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case(sf::Keyboard::Up):
                    if (player.getPosition().y > 100)
                    {
                        player.setPosition(player.getPosition() + sf::Vector2f{ 0, -20 });
                    }
                    break;
                
                case(sf::Keyboard::Down):
                    if (player.getPosition().y < 980)
                    {
                        player.setPosition(player.getPosition() + sf::Vector2f{ 0, 20 });
                    }
                    break;

                case(sf::Keyboard::Left):
                    if (player.getPosition().x > 100)
                    {
                        player.setPosition(player.getPosition() + sf::Vector2f{ -20, 0 });
                    }
                    break;
                case(sf::Keyboard::Right):
                    if (player.getPosition().x < 1800)
                    {
                        player.setPosition(player.getPosition() + sf::Vector2f{ 20, 0 });
                    }
                    break;
                }
            }
        }  

        window.draw(player);
        window.display();
    }


return 0;
}