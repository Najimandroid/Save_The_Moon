#include "Window.h"
#include "Bullet.h"
#include "CustomBullets.h"
#include "Player.h"
#include "Bullet.h"
#include "Music.h"
#include "Menu.h"
#include "Game.h"
#include <iostream>
#include "HealthBar.h"
#include "Player.h"
#include "Level.h"
#include "Enemy.h"
#include "Collectable.h"

#include <vector>   
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <chrono>

BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;
WallManager* WallManager::instance = nullptr;
LevelManager* LevelManager::instance = nullptr;
HealthBarManager* HealthBarManager::instance = nullptr;
WindowConfig* WindowConfig::instance = nullptr;
PlayerManager* PlayerManager::instance = nullptr;
CollectableManager* CollectableManager::instance = nullptr;

BulletManager* bulletManager = BulletManager::getInstance();
EnemyManager* enemyManager = EnemyManager::getInstance();
WallManager* wallManager = WallManager::getInstance();
LevelManager* levelManager = LevelManager::getInstance();
HealthBarManager* healthBarManager = HealthBarManager::getInstance();
WindowConfig* windowConfigs = WindowConfig::getInstance();
CollectableManager* collectableManager = CollectableManager::getInstance();

int main()
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    //creation d'une fenetre
    sf::RenderWindow window(sf::VideoMode(windowConfigs->SIZE_X, windowConfigs->SIZE_Y), "Save The Moon", sf::Style::Fullscreen); //sf::Style::Fullscreen
    window.setFramerateLimit(144);
	sf::RenderWindow window(sf::VideoMode(1900, 1080), "Save The Moon", sf::Style::Fullscreen);
    //test
    //creation d'un objet joueur
    Player* player = new Player({ 100, windowConfigs->SIZE_Y / 2.f }, { WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f }, 150, 20, 3.f, true, .1f);
    sf::RectangleShape player(sf::Vector2f(200, 200));
    float spawnCooldown = 0.f;
    levelManager->loadLevel(2);
    player.setFillColor(sf::Color::Red);
    //creation d'une horloge
    sf::Clock clock;
    float deltaTime;
    player.setOrigin(sf::Vector2f{ player.getSize().x, player.getSize().y } / 2.f);
    bool isPaused = false;

    Music* change = Music::getInstance();
    MenuManager* menu = game.createMenu(window);
    struct LvlAvailable Dispo;
    change->SetSound("TitleScreen.wav");
    sf::Event event;

    while (window.isOpen())
    {
        window.clear();
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close(); // Fermer avec echap
            }


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P)
                    isPaused = !isPaused; // Fermer avec echap
            }
        }

        deltaTime = clock.restart().asSeconds();

        if (!isPaused) 
        {
            levelManager->getBackground()->moveBackground(deltaTime);

            for (Enemy* enemy : enemyManager->getEnemies())
            {
                bulletManager->checkCollisions(enemy);
            }
            bulletManager->checkCollisions(player);
            enemyManager->checkCollisions(player);
            collectableManager->checkCollisions(player);

            wallManager->updatePositions(deltaTime);
            collectableManager->updatePositions(deltaTime);
            player->update(deltaTime);
            enemyManager->update(deltaTime);
            bulletManager->updatePositions(deltaTime);
            healthBarManager->updateBars();
        }

        
        levelManager->getBackground()->drawBackground(window);
        wallManager->drawWalls(window);

        collectableManager->drawCollectables(window);
        player->draw(window, sf::Color::Green);
        enemyManager->drawEnemies(window);
        bulletManager->drawBullets(window);
        healthBarManager->drawBars(window);

            //Bouton Menu Selection Niveau
            if (event.type == sf::Event::MouseButtonPressed)
            {
                menu->activateButton(menu->isMouseOnButton(sf::Mouse::getPosition(window)));
            }
     
        }
        menu->drawButtons(window);
        window.display();
        window.display();

        bulletManager->despawnBullets();

        if (player->getHealth() <= 0) isPaused = true;
    }


    return 0;
}