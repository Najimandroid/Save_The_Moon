#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>

BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;

int main()
{
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(120);

    BulletManager* bulletManager = BulletManager::getInstance();
    EnemyManager* enemyManager = EnemyManager::getInstance();

    //test
    //creation d'un objet joueur
    Player player(100, .1f, { 1900 / 2, 1080 / 2 });

    //creation d'un enemie
    enemyManager->spawnEnemy(100, 25, { 1900, 1080 / 2 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 1080 / 4 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 1080 / 3 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 900 }, 3);

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
                    window.close(); // Fermer avec echap
            }
        }

        bulletManager->despawnBullets();

        bulletManager->drawBullets(window);
        enemyManager->drawEnemies(window);

        for (Enemy* enemy : enemyManager->getEnemies())
        {
            bulletManager->checkCollisions(enemy);
        }

        deltaTime = clock.restart().asSeconds();

        bulletManager->updatePositions(deltaTime);
        enemyManager->update(deltaTime);
        player.update(deltaTime);

        ship.setPosition(player.getPosition());

        window.draw(ship);
        window.display();
    }


    return 0;
}