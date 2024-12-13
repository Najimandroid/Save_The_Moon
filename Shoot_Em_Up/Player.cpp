#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Level.h"
#include "HealthBar.h"
#include "Window.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <cmath>

float DEFAULT_SPEED = 35.0f;
float WALL_OFFSET = 10.f;

//* INIT *\\

void Player::initHit(float hitCooldown_)
{
    this->hit = false;
    this->hitCooldown = 0;

    this->hitCooldownMax = hitCooldown_;
    this->count = 0;
}

//* UPDATING *\\

void Player::updatePosition(float deltaTime)
{
    LevelManager* levelManager = LevelManager::getInstance();
    WallManager* wallManager = WallManager::getInstance();

    for (sf::Keyboard::Key key : this->upKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y > this->hitbox.getSize().y / 2)
        {
            this->velocity = sf::Vector2f{ 0, -levelManager->SCROLLING_SPEED * deltaTime * this->speed };

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
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y < (WindowConfig::getInstance()->SIZE_Y - this->hitbox.getSize().y / 2))
        {
            this->velocity = sf::Vector2f{ 0, levelManager->SCROLLING_SPEED * deltaTime * this->speed };
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
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x > this->hitbox.getSize().x / 2)
        {
            this->velocity = sf::Vector2f{ -levelManager->SCROLLING_SPEED * deltaTime * this->speed , 0 };
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
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x < WindowConfig::getInstance()->SIZE_X - this->hitbox.getSize().x / 2)
        {
            this->velocity = sf::Vector2f{ levelManager->SCROLLING_SPEED * deltaTime * this->speed , 0 };
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
                bulletManager->spawnbullet(this, { this->position }, { 1, 0 }, 2 * this->speed);
            }
        }
    }
    else
    {
        this->shootCooldown += deltaTime;
    }
}

void Player::updateHealth(float value)
{
    if (!this->active) return; // doesn't update health if the entity is inactive

    if (value < 0)
    {
        if (this->hit) return;
        this->hit = true;
    }

    this->health += value;
}

void Player::updateState(float deltaTime)
{
    if (this->hit)
    {
       // std::cout << "player hit\n";
        if (this->isOnHitCooldown())
        {
            this->hitCooldown += deltaTime;
            this->count += deltaTime;
            //std::cout << "player on hit cooldown: " << this->hitCooldown << ", " << this->hitCooldownMax << std::endl;
        }
        else
        {
            this->hit = false;
            this->hitCooldown = 0.f;
            this->count = 0.f;
            //std::cout << "player on hit cooldown is finished\n";
        }
    }

    if (this->position.x < -30)
    {
        this->health = 0;
    }

   /* if (this->isDead()) {
        // delete if dead
        delete this;
        return;
    }*/
}

void Player::draw(sf::RenderWindow& window, sf::Color color)
{
    sf::RectangleShape body_(this->getHitbox().getSize());
    body_.setOrigin(this->getHitbox().getSize() / 2.f);
    body_.setFillColor(color);
    body_.setPosition(this->getPosition());

    //FLASHING EFFECT
    if (this->hit) 
    { 
        if (this->count < .125f) //this->hitCooldownMax/4 
        {
            body_.setFillColor(sf::Color::Transparent);
        }
        else if (this->count < .25f)
        {
            body_.setFillColor(sf::Color::Green);
        }
        else if (this->count > .25f)
        {
            this->count = 0.f;
        }
    }

    window.draw(body_);
}

//* CONSTRUCTOR *\\

Player::Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_)
{
    this->initPosition(position_);
    this->initHitbox(hitboxSize_);
    this->initProperties(health_, damage_, ((speed_ * WindowConfig::getInstance()->SIZE_X) / 1920), canShoot_, cooldownSeconds_);
    this->initHit(1.5f);

    HealthBarManager* healthBarManager = HealthBarManager::getInstance();
    HealthBar* bar = healthBarManager->createHealthBar(health_);

    bar->linkEntity(this);
}