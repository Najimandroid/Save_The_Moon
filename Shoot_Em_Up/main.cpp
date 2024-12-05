#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{

	sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);

    sf::RectangleShape rectangle(sf::Vector2f(200, 200));

    rectangle.setFillColor(sf::Color::Red);

    rectangle.setOrigin(sf::Vector2f{ rectangle.getSize().x, rectangle.getSize().y } / 2.f);
    rectangle.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    window.draw(rectangle);
    window.display();

    while (window.isOpen())
    {
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
    }


return 0;
}