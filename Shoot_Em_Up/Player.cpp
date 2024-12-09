#include "Player.h"
#include "Bullet.h"
#include  <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

float DEFAULT_SPEED = 35.0f;

void Player::updatePosition(float deltaTime)
{
    for (sf::Keyboard::Key key : this->upKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y > 50)
        {
            this->velocity = sf::Vector2f{ 0, -20 * deltaTime * this->speed };
            this->position += this->velocity;
        }
    }

    for (sf::Keyboard::Key key : this->downKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y < 1030)
        {
            this->velocity = sf::Vector2f{ 0, 20 * deltaTime * this->speed };
            this->position += this->velocity;
        }
    }

    for (sf::Keyboard::Key key : this->leftKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x > 50)
        {
            this->velocity = sf::Vector2f{ -20 * deltaTime * this->speed , 0 };
            this->position += this->velocity;
        }
    }

    for (sf::Keyboard::Key key : this->rightKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x < 1875)
        {
            this->velocity = sf::Vector2f{ 20 * deltaTime * this->speed , 0 };
            this->position += this->velocity;
        }
    }
}

void Player::updateShoot(float deltaTime)
{
    if (!this->isOnCooldown())
    {
        //reset cooldown
        this->shootCooldown = 0.f;
     
        //then shoot
        for (sf::Keyboard::Key key : this->shootKeys)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                BulletManager* bulletManager = BulletManager::getInstance();
                bulletManager->spawnbullet({ this->position }, this->speed);
            }
        }
    }
    else
    {
        this->shootCooldown += deltaTime;
    }
}

Player::Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
    this->initPosition(position_);
    this->initHitbox(hitboxSize_);
    this->initProperties(health_, damage_, speed_, canShoot_, cooldownSeconds_);
}