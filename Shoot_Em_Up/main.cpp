#include "Player.h"

#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

int main()
{
    std::vector<sf::Keyboard::Key> UP_KEYS = { sf::Keyboard::Key::Z, sf::Keyboard::Key::Up };
    std::vector<sf::Keyboard::Key> DOWN_KEYS = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
    std::vector<sf::Keyboard::Key> LEFT_KEYS = { sf::Keyboard::Key::Q, sf::Keyboard::Key::Left };
    std::vector<sf::Keyboard::Key> RIGHT_KEYS = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };


	sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Clock clock;
    float deltaTime;
    float playerSpeed = 35.0f;

    sf::RectangleShape player(sf::Vector2f(100, 100));

    player.setFillColor(sf::Color::Green);

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
        }  

        deltaTime = clock.restart().asSeconds();

        for (sf::Keyboard::Key key : UP_KEYS) 
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                player.move(sf::Vector2f{ 0, -20 * deltaTime * playerSpeed });
            }
        }

        for (sf::Keyboard::Key key : DOWN_KEYS)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                player.move(sf::Vector2f{ 0, 20 * deltaTime * playerSpeed });
            }
        }

        for (sf::Keyboard::Key key : LEFT_KEYS)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                player.move(sf::Vector2f{ -20 * deltaTime * playerSpeed, 0 });
            }
        }

        for (sf::Keyboard::Key key : RIGHT_KEYS)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                player.move(sf::Vector2f{ 20 * deltaTime * playerSpeed, 0 });
            }
        }

        window.draw(player);
        window.display();
    }


return 0;
}