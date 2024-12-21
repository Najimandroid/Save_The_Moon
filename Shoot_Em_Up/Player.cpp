#include "Player.h"
#include "Bullet.h"
#include "Wall.h"
#include "Level.h"
#include "HealthBar.h"
#include "Window.h"
#include "SFX.h"

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
    //std::cout << this->score << '\n';

    LevelManager* levelManager = LevelManager::getInstance();
    WallManager* wallManager = WallManager::getInstance();

    for (sf::Keyboard::Key key : this->upKeys)
    {
        if (sf::Keyboard::isKeyPressed(key) && this->getPosition().y > this->hitbox.getSize().y / 2)
        {
            this->velocity = sf::Vector2f{ 0, -levelManager->SCROLLING_SPEED * deltaTime * this->speed * 1080 / WindowConfig::getInstance()->SIZE_Y };

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
            this->velocity = sf::Vector2f{ 0, levelManager->SCROLLING_SPEED * deltaTime * this->speed * 1080 / WindowConfig::getInstance()->SIZE_Y };
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
            this->velocity = sf::Vector2f{ -levelManager->SCROLLING_SPEED * deltaTime * this->speed * 1920 / WindowConfig::getInstance()->SIZE_X, 0 };
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
            this->velocity = sf::Vector2f{ levelManager->SCROLLING_SPEED * deltaTime * this->speed * 1920 / WindowConfig::getInstance()->SIZE_X, 0 };
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
    this->usingPrimary = false;
    if (!this->isOnCooldown())
    {

        //reset cooldown
        this->shootCooldown = 0.f;

        //primary
        for (sf::Keyboard::Key key : this->shootKeys)
        {
            if (sf::Keyboard::isKeyPressed(key))
            {
                SFXManager::getInstance()->play("assets/sfx/Shoot.mp3")->setPitch(.75f);

                this->usingPrimary = true;
                LevelManager* levelManager = LevelManager::getInstance();
                BulletManager* bulletManager = BulletManager::getInstance();
                bulletManager->spawnBullet(this, { this->position }, { 1, 0 }, 2 * this->speed, {0, 0})->setDamage(25);
                return;
            }
        }

        //secondary
        for (sf::Keyboard::Key key : this->secondaryShootKeys)
        {
            if (sf::Keyboard::isKeyPressed(key) && !this->usingPrimary)
            {
                SFXManager::getInstance()->play("assets/sfx/Shoot.mp3")->setPitch(.75f);

                this->usingPrimary = false;
                LevelManager* levelManager = LevelManager::getInstance();
                BulletManager* bulletManager = BulletManager::getInstance();
                bulletManager->spawnBullet(this, { this->position }, { 1, 0.25 }, 2 * this->speed, { 1, 0 })->setDamage(10);
                bulletManager->spawnBullet(this, { this->position }, { 1, -0.25 }, 2 * this->speed, { 1, 0 })->setDamage(10);
                return;
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
        SFXManager::getInstance()->play("assets/sfx/Hurt.mp3");
    }

    if (this->health + value >= this->maxHealth)
    {
        this->health += this->maxHealth - this->health;
    }
    else
    {
        this->health += value;
    }
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

//* GRAPHICS *\\

bool PlayerManager::loadTextures()
{
    if (!this->texture.loadFromFile("assets/textures/Players.png")) return false;
    setSprites();
    return true;
}

void PlayerManager::setSprites()
{
    for (Player* adress : this->players)
    {
        if (adress->getSprite() != nullptr) continue;

        sf::Sprite* sprite = new sf::Sprite;

        sprite->setScale({ adress->getHitbox().getSize().x * 2.5f / 60, adress->getHitbox().getSize().y * 2.5f / 60 });
        sprite->setOrigin({
            adress->getHitbox().getOrigin().y / sprite->getScale().y,
            adress->getHitbox().getOrigin().y / sprite->getScale().y
            });
        sprite->setTexture(this->texture);

        sprite->setTextureRect(sf::IntRect(
            adress->getTextureCoords().x * LevelManager::getInstance()->TILE_SIZE / 2,
            adress->getTextureCoords().y * LevelManager::getInstance()->TILE_SIZE / 2,
            LevelManager::getInstance()->TILE_SIZE / 2,
            LevelManager::getInstance()->TILE_SIZE / 2));

        adress->setSprite(sprite);
    }
}

void Player::draw(sf::RenderWindow& window)
{
    if (!this->getSprite()) return;

    //FLASHING EFFECT
    if (this->hit) 
    { 
        if (this->count < .125f) //this->hitCooldownMax/4 
        {
            this->getSprite()->setColor(sf::Color::Transparent);
        }
        else if (this->count < .25f)
        {
            this->getSprite()->setColor(sf::Color::White);
        }
        else if (this->count > .25f)
        {
            this->count = 0.f;
        }
    }

    if (this->getPosition().x >= WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X / 10) { return; }

    this->sprite->setPosition(this->getPosition());
    this->sprite->setRotation(this->hitbox.getRotation());

    window.draw(*this->getSprite());
}

//* CONSTRUCTOR *\\

Player::Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_,sf::Vector2f textureCoords_)
{
    this->initPosition(position_);
    this->initHitbox(hitboxSize_);
    this->initProperties(health_, damage_, ((speed_ * WindowConfig::getInstance()->SIZE_X) / 1920), canShoot_, cooldownSeconds_);
    this->initHit(1.5f);
    this->score = 0;

    this->textureCoords = textureCoords_;

    HealthBarManager* healthBarManager = HealthBarManager::getInstance();
    HealthBar* bar = healthBarManager->createHealthBar(health_);

    bar->linkEntity(this);

    PlayerManager::getInstance()->getPlayers().push_back(this);

    PlayerManager::getInstance()->setSprites();
}