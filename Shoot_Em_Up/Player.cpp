#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Level.h"
#include "HealthBar.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <cmath>

float DEFAULT_SPEED = 35.0f;
float WALL_OFFSET = 10.f;

//* UPDATING *\\

void Player::updatePosition(float deltaTime)
{
    WallManager* wallManager = WallManager::getInstance();
    for (sf::Keyboard::Key key : this->upKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y > 50)
        {
            this->velocity = sf::Vector2f{ 0, -20 * deltaTime * this->speed };

            if (wallManager->detectCollision(this->position + this->velocity, this->hitbox.getSize()))
            {
                this->position +=
                {wallManager->getWallsVelocity().x* (((wallManager->getWallsVelocity().x / deltaTime) - WALL_OFFSET) / (wallManager->getWallsVelocity().x / deltaTime)), 0 };

                this->hitbox.setPosition(this->position);
            }
            else {
                this->position += this->velocity;
                this->hitbox.setPosition(this->position);
            }
        }
    }

    for (sf::Keyboard::Key key : this->downKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y < 1030)
        {
            this->velocity = sf::Vector2f{ 0, 20 * deltaTime * this->speed };
            if (wallManager->detectCollision(this->position + this->velocity, this->hitbox.getSize()))
            {
                this->position +=
                {wallManager->getWallsVelocity().x* (((wallManager->getWallsVelocity().x / deltaTime) - WALL_OFFSET) / (wallManager->getWallsVelocity().x / deltaTime)), 0 };
                this->hitbox.setPosition(this->position);
            }
            else {
                this->position += this->velocity;
                this->hitbox.setPosition(this->position);
            }
        }
    }

    for (sf::Keyboard::Key key : this->leftKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x > 50)
        {
            this->velocity = sf::Vector2f{ -20 * deltaTime * this->speed , 0 };
            if (wallManager->detectCollision(this->position + this->velocity, this->hitbox.getSize()))
            {
                this->position +=
                {(wallManager->getWallsVelocity().x* (abs(this->velocity.x)) / this->velocity.x)* (((wallManager->getWallsVelocity().x / deltaTime) - WALL_OFFSET) / (wallManager->getWallsVelocity().x / deltaTime)), 0 };
                this->hitbox.setPosition(this->position);
            }
            else {
                this->position += this->velocity;
                this->hitbox.setPosition(this->position);
            }
        }
    }

    for (sf::Keyboard::Key key : this->rightKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x < 1875)
        {
            this->velocity = sf::Vector2f{ 20 * deltaTime * this->speed , 0 };
            if (wallManager->detectCollision(this->position + this->velocity, this->hitbox.getSize()))
            {
                this->position +=
                {wallManager->getWallsVelocity().x* (((wallManager->getWallsVelocity().x / deltaTime) - WALL_OFFSET) / (wallManager->getWallsVelocity().x / deltaTime)), 0 };
                this->hitbox.setPosition(this->position);
            }
            else {
                this->position += this->velocity;
                this->hitbox.setPosition(this->position);
            }
        }
    }

    //update even if not moving
    if (wallManager->detectCollision(this->position, this->hitbox.getSize()))
    {
        this->position +=
        {wallManager->getWallsVelocity().x* (((wallManager->getWallsVelocity().x / deltaTime) - WALL_OFFSET) / (wallManager->getWallsVelocity().x / deltaTime)), 0 };
        this->hitbox.setPosition(this->position);
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
                LevelManager* levelManager = LevelManager::getInstance();
                BulletManager* bulletManager = BulletManager::getInstance();
                bulletManager->spawnbullet(this, { this->position }, 2 * this->speed);
            }
        }
    }
    else
    {
        this->shootCooldown += deltaTime;
    }
}

//* CONSTRUCTOR *\\

Player::Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
    this->initPosition(position_);
    this->initHitbox(hitboxSize_);
    this->initProperties(health_, damage_, speed_, canShoot_, cooldownSeconds_);

    HealthBarManager* healthBarManager = HealthBarManager::getInstance();
    HealthBar* bar = healthBarManager->createHealthBar(health_);

    bar->linkEntity(this);
}