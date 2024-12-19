#include "Game.h"

BulletManager* bulletManager = BulletManager::getInstance();
EnemyManager* enemyManager = EnemyManager::getInstance();
WallManager* wallManager = WallManager::getInstance();
LevelManager* levelManager = LevelManager::getInstance();
HealthBarManager* healthBarManager = HealthBarManager::getInstance();
WindowConfig* windowConfigs = WindowConfig::getInstance();
CollectableManager* collectableManager = CollectableManager::getInstance();
Music* music = Music::getInstance();

Game::Game()
{
	gameStarted = false;
    deltaTime = 0.f;
    isPaused = false;
    currentLevel = 0;
}

void Game::initSeed()
{
	srand(std::chrono::system_clock::now().time_since_epoch().count());
}


MenuManager* Game::createMenu(sf::RenderWindow& window)
{
	return new MenuManager;
}

void Game::startLevel(int levelIndex_)
{
    currentLevel = levelIndex_;
    if (levelIndex_ > 0)
    {
        gameStarted = true;
        Player* player = new Player({ 100, windowConfigs->SIZE_Y / 2.f }, { WindowConfig::getInstance()->SIZE_Y / 18.f, WindowConfig::getInstance()->SIZE_Y / 18.f }, 150, 20, 3.f, true, .1f, {1, 0});
        levelManager->loadLevel(levelIndex_);
    }
    isPaused = false;
}

void Game::checkGameCollisions()
{
    for (Enemy* enemy : enemyManager->getEnemies())
    {
        bulletManager->checkCollisions(enemy);
    }

    for (Player* player : PlayerManager::getInstance()->getPlayers())
    {
        bulletManager->checkCollisions(player);
        enemyManager->checkCollisions(player);
        collectableManager->checkCollisions(player);
    }
}

void Game::updateGameObjects(float deltaTime_)
{
    wallManager->updatePositions(deltaTime_);
    collectableManager->updatePositions(deltaTime_);
    enemyManager->update(deltaTime_);
    bulletManager->updatePositions(deltaTime_);
    healthBarManager->updateBars();

    for (Player* player : PlayerManager::getInstance()->getPlayers())
    {
        player->update(deltaTime_);
    }
}

void Game::drawGameObjects(sf::RenderWindow& window)
{
    levelManager->getBackground()->drawBackground(window);
    wallManager->drawWalls(window);

    collectableManager->drawCollectables(window);

    for (Player* player : PlayerManager::getInstance()->getPlayers())
    {
        player->draw(window);
    }

    enemyManager->drawEnemies(window);
    bulletManager->drawBullets(window);
    healthBarManager->drawBars(window);
}

void Game::Gameloop(sf::RenderWindow& window, MenuManager* menuManager)
{

    while (window.isOpen())
    {
       
        window.clear();
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        while (window.pollEvent(this->event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close(); // Fermer avec echap
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::P && this->gameStarted)
                    isPaused = !isPaused;
            }

            if (event.type == sf::Event::MouseButtonPressed && !gameStarted)
            {
                menuManager->activateButton(menuManager->isMouseOnButton(sf::Mouse::getPosition(window)));
            }
        }
        
        deltaTime = clock.restart().asSeconds();


        if (!gameStarted)
        {
            menuManager->drawButtons(window);
            if (menuManager->readyForLevel != 0)
            {
                startLevel(menuManager->readyForLevel);
            }
        }
        else
        {
            if (!isPaused)
            {
                levelManager->getBackground()->moveBackground(deltaTime);

                checkGameCollisions();
                updateGameObjects(deltaTime);
            }

            drawGameObjects(window);

            bulletManager->despawnBullets();

            bool areAllPlayersDead = true;
            for (Player* player : PlayerManager::getInstance()->getPlayers())
            {
                if (player->getHealth() > 0) areAllPlayersDead = false;
            }
            if (areAllPlayersDead) 
            { 
                levelManager->unloadLevel(); 
                gameStarted = false; 
                areAllPlayersDead = false; 
                menuManager->readyForLevel = 0; 
                menuManager->openMenu(); 
            }
        }

        window.display();
        
    }

}
