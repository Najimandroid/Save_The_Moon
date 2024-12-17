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
}

Collectable::Collectable(sf::Vector2f position_, void(*effect_)())
{
	this->position = position_;
	this->sprite = nullptr;
	this->target = nullptr;

	this->effect = effect_;

	this->hitbox.setSize({ 25, 25 });
	this->hitbox.setOrigin({ 25 / 2, 25 / 2 });
	this->hitbox.setPosition(this->position);
}

Collectable::~Collectable()
{
	this->setSprite(nullptr);
}

bool Collectable::collided(Entity* entity)
{
	if (!entity->isPlayer()) { return false; } //ignore if not player

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

void Collectable::collected()
{
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
	case COIN: newCollect = new Collectable(position, []() { std::cout << "Coin collected!\n"; }); break;
	case HEART: newCollect = new Collectable(position, []() { std::cout << "+20 HP!\n"; }); break;
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

		std::cout << adress->getTextureCoords().x << ", " << adress->getTextureCoords().y << std::endl;

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

void CollectableManager::checkCollisions(Entity* entity)
{
	unsigned index = 0;
	for (Collectable* adress : this->collectables)
	{
		if (adress == nullptr) { index++;  continue; }

		if (adress->collided(entity))
		{
			adress->collected();

			//delete
			delete this->collectables.at(index);
			this->collectables.erase(this->collectables.begin() + index);
			index--;
		}
		index++;
	}
}