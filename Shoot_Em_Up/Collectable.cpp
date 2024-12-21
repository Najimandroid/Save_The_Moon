#include "Collectable.h"

Collectable::Collectable()
{
	this->position = { 0, 0 };
	this->sprite = nullptr;
	this->target = nullptr;


	this->effect = [&]()
		{
			std::cout << "Collected!\n";
		};

	this->hitbox.setSize({ 0, 0 });

	this->textureCoords = { 0, 0 };
	this->type = COIN;
}

Collectable::Collectable(sf::Vector2f position_, sf::Vector2f textureCoords_, CollectableType type_)
{
	this->position = position_;
	this->sprite = nullptr;
	this->target = nullptr;

	this->effect = [&]()
		{
			std::cout << "Collected!\n";
		};;

	this->hitbox.setSize({ 25, 25 });
	this->hitbox.setOrigin({ 25 / 2, 25 / 2 });
	this->hitbox.setPosition(this->position);

	this->textureCoords = textureCoords_;
	this->type = type_;
}

Collectable::~Collectable()
{
	this->setSprite(nullptr);
}

bool Collectable::collided(Player* entity)
{
	if (!entity->isPlayer()) { return false; } //ignore if not player

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

void Collectable::collected()
{
	switch (this->type)
	{
	case COIN: 
		this->setEffect([&]() { if (this->getTarget()) { SFXManager::getInstance()->play("assets/sfx/Coin.mp3"); this->getTarget()->updateScore(5); }});
		break;
	case HEART:
		this->setEffect([&]() {if (this->getTarget()) { std::cout << "Heart collected!\n"; if (this->getTarget()) this->getTarget()->updateHealth(20); }});
		break;
	}
	this->effect();
}

void Collectable::updatePosition(float deltaTime)
{
	this->position = { this->position.x + -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, this->position.y };
	this->hitbox.setPosition(this->position);
}


Collectable* CollectableManager::spawnCollectable(sf::Vector2f position, CollectableType type)
{

	Collectable* newCollect = nullptr;

	switch (type)
	{
	case COIN: newCollect = new Collectable(position, {0, 0}, CollectableType::COIN); break;
	case HEART: newCollect = new Collectable(position, { 1, 2 }, CollectableType::HEART); break;
	}

	if (newCollect == nullptr) return spawnCollectable(position, CollectableType::COIN);

	this->collectables.push_back(newCollect);
	setSprites();
	return newCollect;
}

void CollectableManager::updatePositions(float deltaTime)
{
	for (Collectable* adress : this->collectables)
	{
		adress->updatePosition(deltaTime);
	}
}

bool CollectableManager::loadTexture()
{
	if (!this->texture.loadFromFile("assets/textures/Collectables.png")) return false;
	setSprites();
	return true;
}

void CollectableManager::setSprites()
{
	for (Collectable* adress : this->collectables)
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

		sprite->setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * LevelManager::getInstance()->TILE_SIZE / 4,
			adress->getTextureCoords().y * LevelManager::getInstance()->TILE_SIZE / 4,
			LevelManager::getInstance()->TILE_SIZE / 4,
			LevelManager::getInstance()->TILE_SIZE / 4));

		adress->setSprite(sprite);
	}
}

void CollectableManager::drawCollectables(sf::RenderWindow& window)
{
	for (Collectable* adress : this->collectables)
	{
		if (!adress->getSprite()) continue;
		if (adress->getPosition().x >= WindowConfig::getInstance()->SIZE_X + WindowConfig::getInstance()->SIZE_X / 10) { continue; }


		adress->getSprite()->setPosition(adress->getPosition());

		window.draw(*adress->getSprite());
	}
}

void CollectableManager::checkCollisions(Player* entity)
{
	unsigned index = 0;
	for (Collectable* adress : this->collectables)
	{
		if (adress == nullptr) { index++;  continue; }

		if (adress->collided(entity))
		{
			adress->setTarget(entity);
			adress->collected();

			//delete
			delete this->collectables.at(index);
			this->collectables.erase(this->collectables.begin() + index);
			index--;
		}
		index++;
	}
}