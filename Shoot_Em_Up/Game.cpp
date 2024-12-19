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

    font = new sf::Font;
    if (!font->loadFromFile("assets/fonts/upheavtt.ttf"))
    {
        std::cout << "Font not found!\n";
    }
   
    scoreText = new sf::Text;
    scoreText->setFont(*font);
    scoreText->setCharacterSize(60);
    scoreText->setFillColor(sf::Color(172, 247, 235));
    scoreText->setOutlineThickness(2.f);
    scoreText->setOutlineColor(sf::Color::Black);

    sf::FloatRect bounds = scoreText->getLocalBounds();
    scoreText->setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
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
    scoreText->setPosition({ windowConfigs->SIZE_X - scoreText->getLocalBounds().width /2.f - 200, windowConfigs->SIZE_Y - scoreText->getLocalBounds().height / 2 - 60 });
    scoreText->setString("[SCORE]: " + std::to_string(static_cast<int>(PlayerManager::getInstance()->getPlayers()[0]->getScore())));

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

    window.draw(*scoreText);
}

void Game::Gameloop(sf::RenderWindow& window, MenuManager* menuManager)
{

    while (window.isOpen())
    {
       
        window.clear();
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        //std::cout << mouse.x << ", " << mouse.y << std::endl;

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
                if (menuManager->isMouseOnButton(sf::Mouse::getPosition(window)) == QUIT)
                {
                    window.close();
                }
                menuManager->activateButton(menuManager->isMouseOnButton(sf::Mouse::getPosition(window)));
            }
        }
        
        deltaTime = clock.restart().asSeconds();


        if (!gameStarted)
        {
            scoreText->setString(' ');
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
                menuManager->openLose(); 
            }

            if (levelManager->levelCompleted)
            {
                levelManager->getCompletion()[currentLevel - 1] = 1;

                levelManager->unloadLevel();
                gameStarted = false;
                menuManager->readyForLevel = 0;
                menuManager->openVictory();
            }
        }

        window.display();
        
    }

}
