#include "Wall.h"

bool Wall::collided(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize)
{
	sf::RectangleShape checkHitbox(entityHitboxSize);
	checkHitbox.setOrigin(entityHitboxSize / 2.f);
	checkHitbox.setPosition(targetPosition);

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = checkHitbox.getGlobalBounds();

	return(floatRect.intersects(otherFloatRect));
}

void Wall::initHitbox(sf::Vector2f hitboxSize_)
{
	sf::RectangleShape hitbox_(sf::Vector2f(hitboxSize_.x, hitboxSize_.y));
	this->hitbox = hitbox_;
	this->hitbox.setOrigin(hitboxSize_ / 2.f);
	this->hitbox.setPosition(this->position);
}

Wall::~Wall()
{
	this->setSprite(nullptr);
}

Wall* WallManager::spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize)
{
	Wall* newWall = new Wall(position, hitboxSize);
	this->walls.push_back(newWall);
	setSprites();
	return newWall;
}

Wall* WallManager::spawnWall(sf::Vector2f position, sf::Vector2f hitboxSize, bool isBreakable, float health)
{
	Wall* newWall = new Wall(position, hitboxSize, isBreakable, health);
	this->walls.push_back(newWall);
	setSprites();
	return newWall;
}

sf::Vector2f WallManager::getWallsVelocity()
{
	return this->walls[0]->getVelocity();
}

void WallManager::setSprites()
{
	for (Wall* adress : this->walls)
	{
		if (adress->getSprite() != nullptr) continue;

		sf::Sprite* sprite = new sf::Sprite;
		sprite->setTexture(this->texture);
		sprite->setScale({ 2, 2 });

		sprite->setOrigin({
			adress->getHitbox().getOrigin().y / sprite->getScale().y,
			adress->getHitbox().getOrigin().y / sprite->getScale().y
			});
		//adress->getSprite()->setOrigin({ 30 / 2.f }, { 30 / 2.f });

		std::cout << adress->getTextureCoords().x << ", " << adress->getTextureCoords().y << std::endl;
			 
		sprite->setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * LevelManager::getInstance()->TILE_SIZE / 2,
			adress->getTextureCoords().y * LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2));

		adress->setSprite(sprite);
	}
}

bool WallManager::loadTexture()
{
	if (!this->texture.loadFromFile("assets/textures/Walls.png")) return false;
	setSprites();
	return true;
}

void WallManager::drawWalls(sf::RenderWindow& window)
{
	for (Wall* adress : this->walls)
	{
		if (!adress->getSprite()) continue;
		if (adress->getPosition().x >= WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X / 10) { continue; }

		
		adress->getSprite()->setPosition(adress->getPosition());

		window.draw(*adress->getSprite());
	}
}

void WallManager::updatePositions(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	for (Wall* wall : this->walls)
	{
		wall->setVelocity(sf::Vector2f{ -levelManager->SCROLLING_SPEED * deltaTime, 0 });
		wall->setPosition(wall->getPosition() + wall->getVelocity());
		wall->getHitbox().setPosition(wall->getPosition());
	}
}

bool WallManager::detectCollision(sf::Vector2f targetPosition, sf::Vector2f entityHitboxSize)
{
	for (Wall* wall : this->walls)
	{
		if (wall->collided(targetPosition, entityHitboxSize)) return true;
	}
	return false;
}