#include "Game.h"

//* INITIALIZATION OF ALL MANAGERS *\\

BulletManager* BulletManager::instance = nullptr;
EnemyManager* EnemyManager::instance = nullptr;
WallManager* WallManager::instance = nullptr;
LevelManager* LevelManager::instance = nullptr;
HealthBarManager* HealthBarManager::instance = nullptr;
WindowConfig* WindowConfig::instance = nullptr;
PlayerManager* PlayerManager::instance = nullptr;
CollectableManager* CollectableManager::instance = nullptr;
Music* Music::instance = nullptr;
SFXManager* SFXManager::instance = nullptr;

int main()
{

    // Creation of the window
    sf::RenderWindow window(sf::VideoMode(WindowConfig::getInstance()->SIZE_X, WindowConfig::getInstance()->SIZE_Y), "Save The Moon", sf::Style::Fullscreen); //sf::Style::Fullscreen
    window.setFramerateLimit(120);

    Game game;
    game.initSeed();

   // levelManager->loadLevel(1);

    game.Gameloop(window, game.createMenu(window));

    return 0;
}