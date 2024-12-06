#include "Player.h"
#include "Bullet.h"
#include  <SFML/Graphics.hpp>
#include <iostream>

float DEFAULT_SPEED = 35.0f;

void Player::shootCheck()
{
    {
        for (sf::Keyboard::Key key : shootKeys)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                BulletManager* instance = BulletManager::getInstance();
                instance->spawnbullet({ this->position });
            }
        }
    }
}

void Player::updatePosition(float deltaTime)
{
    for (sf::Keyboard::Key key : upKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y > 0 )
        {
            this->velocity = sf::Vector2f{ 0, -20 * deltaTime * this->speed };
            this->position += this->velocity; 
        }
    }

    for (sf::Keyboard::Key key : downKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y < 1030)
        {
            this->velocity = sf::Vector2f{ 0, 20 * deltaTime * this->speed };
            this->position += this->velocity;
        }
    }

    for (sf::Keyboard::Key key : leftKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x > 0)
        {
            this->velocity = sf::Vector2f{ -20 * deltaTime * this->speed , 0  };
            this->position += this->velocity;
        }
    }

    for (sf::Keyboard::Key key : rightKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().x < 1850)
        {
            this->velocity = sf::Vector2f{ 20 * deltaTime * this->speed , 0 };
            this->position += this->velocity;
        }
    }
}

void Player::init(float health_, sf::Vector2f position_)
{
    this->health = health_;
    this->position = position_;

    this->velocity = { 0, 0 };
    this->speed = DEFAULT_SPEED;

}

Player::Player(float health_, sf::Vector2f position_)
{
    Player::init(health_, position_);
}