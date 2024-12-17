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


Collectable* CollectableManager::spawnCollectable(sf::Vector2f position)
{
	Collectable* newCollect = new Collectable(position, []()
		{
			std::cout << "Collected!\n";
		});

	this->collectables.push_back(newCollect);
	return newCollect;
}

void CollectableManager::updatePositions(float deltaTime)
{
	for (Collectable* adress : this->collectables)
	{
		adress->updatePosition(deltaTime);
	}
}

void CollectableManager::drawCollectables(sf::RenderWindow& window)
{
	for (Collectable* adress : this->collectables)
	{
		sf::RectangleShape body({ adress->getHitbox().getSize().x, adress->getHitbox().getSize().y });
		body.setOrigin({ body.getSize().x / 2, body.getSize().y / 2 });
		body.setPosition(adress->getPosition());
		body.setFillColor(sf::Color::Yellow);

		window.draw(body);
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