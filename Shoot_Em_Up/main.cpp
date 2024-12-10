#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>
#include <ctime>

BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;

BulletManager* bulletManager = BulletManager::getInstance();
EnemyManager* enemyManager = EnemyManager::getInstance();

void spawnEnemiesTest()
{
    enemyManager->spawnEnemy(500, 25, { 1900, 950 / float(rand() % 5 + 1)}, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 950 / float(rand() % 5 + 1) }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 950 / float(rand() % 5 + 1) }, 3);
    enemyManager->spawnEnemy(100, 25, { 1900, 950 / float(rand() % 5 + 1) }, 3);
}

int main()
{
    srand(time(NULL));
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(120);

    //test
    //creation d'un objet joueur
    Player* player = new Player({ 1900 / 2, 1080 / 2 }, { 100, 100 }, 100, 20, 20, true, .1f);

    float spawnCooldown = 0.f;
    spawnEnemiesTest();

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

        deltaTime = clock.restart().asSeconds();
        spawnCooldown += deltaTime;

        if (spawnCooldown >= 5.f) {
            spawnCooldown = 0.f;
            spawnEnemiesTest();
        }

        for (Enemy* enemy : enemyManager->getEnemies())
        {
            bulletManager->checkCollisions(enemy);
            bulletManager->checkCollisions(player);
        }

        bulletManager->updatePositions(deltaTime);
        enemyManager->update(deltaTime);
        player->update(deltaTime);


        bulletManager->drawBullets(window);
        player->draw(window, { 100, 100 }, sf::Color::Green);
        enemyManager->drawEnemies(window);

        window.display();

        bulletManager->despawnBullets();
    }


    return 0;
}