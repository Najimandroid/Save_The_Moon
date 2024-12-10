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
    Player* player = new Player({ 1900 / 2, 1080 / 2 }, { 100, 100 }, 100, 20, 20, true, .1f);

    //creation d'un enemie
    enemyManager->spawnEnemy(500, 25, { 1900, 1080 / 2 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 1080 / 4 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 1080 / 3 }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 900 }, 3);

    //creation d'une horloge
    sf::Clock clock;
    float deltaTime;

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
        player->draw(window, { 100, 100 }, sf::Color::Green);
        enemyManager->drawEnemies(window);

        for (Enemy* enemy : enemyManager->getEnemies())
        {
            bulletManager->checkCollisions(enemy);
            bulletManager->checkCollisions(player);
        }

        deltaTime = clock.restart().asSeconds();

        bulletManager->updatePositions(deltaTime);
        enemyManager->update(deltaTime);
        player->update(deltaTime);

        window.display();
    }


    return 0;
}