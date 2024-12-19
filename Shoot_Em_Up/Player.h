#pragma once
#include "Entity.h"

#include <iostream>
#include <vector> 
#include <SFML/Graphics.hpp>

<<<<<<< HEAD
class Player : public Entity
{
private:

	bool hit; // checks if player is hit (imune ti damage during that state)
	float hitCooldown;
	float hitCooldownMax;
	float count; //used to do the flashing effect

	float score;

	//* CONTROL KEYS *\\

	typedef std::vector<sf::Keyboard::Key> KeyVector;

	KeyVector upKeys = { sf::Keyboard::Key::Z };
	KeyVector downKeys = { sf::Keyboard::Key::S };
	KeyVector leftKeys = { sf::Keyboard::Key::Q };
	KeyVector rightKeys = { sf::Keyboard::Key::D };

	KeyVector shootKeys = { sf::Keyboard::Key::Space };
	KeyVector secondaryShootKeys = { sf::Keyboard::Key::LShift };

	bool usingPrimary = true;

public:
	Player(sf::Vector2f position_, sf::Vector2f hitboxSize_, float health_, float damage_, float speed_, bool canShoot_, float cooldownSeconds_);

	float getScore() { return score; }
	void updateScore(float addedScore) { score += addedScore; }

	void initHit(float hitCooldown_);

	bool isOnHitCooldown() { return (hit && (this->hitCooldown < this->hitCooldownMax)); } 

	void updateShoot(float deltaTime) override;
	void updatePosition(float deltaTime) override;
	void updateState(float deltaTime) override;
	void updateHealth(float value) override;

	void draw(sf::RenderWindow& window, sf::Color color);
};

class PlayerManager
{
private:
	static PlayerManager* instance;

	std::vector <Player*> players;

	PlayerManager() {}
public:
	static PlayerManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new PlayerManager();
		}
		return instance;
	}

	std::vector<Player*>& getPlayers()
	{
		return players;
	}
};
=======

class Player
{
private:
	//Main Properties
	float health;

	sf::Vector2f position;
	sf::Vector2f velocity;
    float speed;

	//Movement keys
	typedef std::vector<sf::Keyboard::Key> KeyVector;

	KeyVector upKeys = { sf::Keyboard::Key::Z, sf::Keyboard::Key::Up };
	KeyVector downKeys = { sf::Keyboard::Key::S, sf::Keyboard::Key::Down };
	KeyVector leftKeys = { sf::Keyboard::Key::Q, sf::Keyboard::Key::Left };
	KeyVector rightKeys = { sf::Keyboard::Key::D, sf::Keyboard::Key::Right };

	KeyVector shootKeys = { sf::Keyboard::Key::Space };

public:

	Player(float health_, sf::Vector2f position_);

	sf::Vector2f getPosition() const
	{
		return position;
	}

	void init(float health_, sf::Vector2f position_);

	void shootCheck();
	void updatePosition(float deltaTime);

};
>>>>>>> Bullet
