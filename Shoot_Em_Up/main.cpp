#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"
#include "Level.h"
#include "HealthBar.h"

#include <iostream>
#include <vector>   
#include <SFML/Graphics.hpp>
#include <chrono>

BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;
WallManager* WallManager::instance = nullptr;
LevelManager* LevelManager::instance = nullptr;
HealthBarManager* HealthBarManager::instance = nullptr;

BulletManager* bulletManager = BulletManager::getInstance();
EnemyManager* enemyManager = EnemyManager::getInstance();
WallManager* wallManager = WallManager::getInstance();
LevelManager* levelManager = LevelManager::getInstance();
HealthBarManager* healthBarManager = HealthBarManager::getInstance();

int main()
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Save The Moon", sf::Style::Fullscreen);
    window.setFramerateLimit(120);

    //test
    //creation d'un objet joueur
    Player* player = new Player({ 1900 / 2, 1080 / 2 }, { 50, 50 }, 100, 20, 20, true, .1f);

    float spawnCooldown = 0.f;
    levelManager->loadLevel(1);

    //creation d'une horloge
    sf::Clock clock;
    float deltaTime;

    bool isPaused = false;

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

        if (!isPaused) 
        {
            for (Enemy* enemy : enemyManager->getEnemies())
            {
                bulletManager->checkCollisions(enemy);
            }
            bulletManager->checkCollisions(player);

            wallManager->updatePositions(deltaTime);
            player->update(deltaTime);
            enemyManager->update(deltaTime);
            bulletManager->updatePositions(deltaTime);
            healthBarManager->updateBars();
        }

        wallManager->drawWalls(window);
        player->draw(window, sf::Color::Green);
        enemyManager->drawEnemies(window);
        bulletManager->drawBullets(window);
        healthBarManager->drawBars(window);

        window.display();

        bulletManager->despawnBullets();

        if (player->getHealth() <= 0) isPaused = true;
    }


    return 0;
}