#include "fonction.h"
#include <iostream>
#include  <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
	RenderWindow Game(VideoMode(1900, 1080, "Save The Moon"), );

    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == Keyboard::Escape)
                    window.close(); // Fermer avec Échap
            }
        }
    }
return 0;
}