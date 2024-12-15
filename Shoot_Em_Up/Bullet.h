#pragma once
#include "Entity.h"
#include "Window.h"

#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>


class Bullet
{
private:
	float damage;
	float speed;

	sf::Vector2f textureCoords;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Vector2f direction;

	sf::RectangleShape hitbox;

	Entity* owner;

	sf::Color color;

public:
	Bullet(float damage_, float speed_, sf::Vector2f position_, sf::Vector2f direction_, sf::Vector2f textureCoords_) :
		damage(damage_), speed(speed_), position(position_), velocity({0, 0}), direction(direction_), owner(nullptr), color(sf::Color::White), textureCoords(textureCoords_)
	{
		sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y/108, WindowConfig::getInstance()->SIZE_Y / 108));
		hitbox = hitbox_;
		hitbox.setPosition(position);
	}

	Bullet(float damage_, float speed_, sf::Vector2f position_, sf::Vector2f direction_) :
		damage(damage_), speed(speed_), position(position_), velocity({ 0, 0 }), direction(direction_), owner(nullptr), color(sf::Color::White), textureCoords({ 1, 1 })
	{
		sf::RectangleShape hitbox_(sf::Vector2f(WindowConfig::getInstance()->SIZE_Y / 108, WindowConfig::getInstance()->SIZE_Y / 108));
		hitbox = hitbox_;
		hitbox.setPosition(position);
	}

	//* GET *\\

	float getSpeed() const { return speed; }
	float getDamage() { return damage; }

	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getVelocity() const { return velocity; }
	sf::Vector2f getDirection() const { return direction; }
	sf::Vector2f getTextureCoords() const { return textureCoords; }

	sf::RectangleShape& getHitbox() { return hitbox; }
	sf::Color getColor() { return color; }

	Entity* getOwner() { return owner; }

	//* SET *\\

	void setPosition(sf::Vector2f newPosition) { position = newPosition; }
	void setVelocity(sf::Vector2f newVelocity) { velocity = newVelocity; }
	void setDamage(float newDamage) { damage = newDamage; }

	void setColor(sf::Color newColor) { color = newColor; }
		
	void setOwner(Entity* owner_) { 
		if (owner_ == nullptr) { std::cout << "Can't set a bullet's owner with nullptr\n" ; return; }
		owner = owner_; 
	}
	void setNullOwner() { owner = nullptr; }

	//* BOOLEANS *\\

	bool collided(Entity* obstacle);
};



class BulletManager
{
private:
	static BulletManager* instance;

	sf::Texture texture;
	std::vector <Bullet*> bullets;

	BulletManager() { if (!loadTexture()) std::cout << "Bullets texture not loaded!"; }
public:
	static BulletManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new BulletManager();
		}
		return instance;
	}

	Bullet* spawnbullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed);
	Bullet* spawnbullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed, sf::Vector2f textureCoords);

	void moveBullet(float deltatime, Bullet* bullet);

	void despawnBullets();

	bool loadTexture();
	void drawBullets(sf::RenderWindow& window);

	void updatePositions(float deltaTime);
	void updateOwners(Entity* entity);

	std::vector<Bullet*> getBullets()
	{
		return bullets;
	}

	

	void checkCollisions(Entity* obstacle);
};