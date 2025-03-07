#include "Bullet.h"
#include "CustomBullets.h"
#include "Boss.h"

//--------------------//* BULLET *\\--------------------\\

//* BOOLEANS *\\

bool Bullet::collided(Entity* entity)
{

	if (dynamic_cast<Enemy*>(this->getOwner()) && dynamic_cast<Enemy*>(entity)) { return false; } //ignore if from same type
	if (dynamic_cast<Player*>(this->getOwner()) && dynamic_cast<Player*>(entity)) { return false; } //ignore if from same type

	sf::FloatRect  floatRect = this->hitbox.getGlobalBounds();
	sf::FloatRect  otherFloatRect = entity->getHitbox().getGlobalBounds();
	return(floatRect.intersects(otherFloatRect));
}

void Bullet::updatePosition(float deltaTime)
{
	this->setVelocity({ WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().x * 1920 / WindowConfig::getInstance()->SIZE_X
					, WindowConfig::getInstance()->SIZE_X / 96 * deltaTime * this->getSpeed() * this->getDirection().y * 1920 / WindowConfig::getInstance()->SIZE_X });
	this->setPosition(this->getPosition() + this->getVelocity());

	//make them follow the scrolling speed

	this->setVelocity({ -LevelManager::getInstance()->SCROLLING_SPEED * deltaTime, 0});
	this->setPosition(this->getPosition() + this->getVelocity());

	this->getHitbox().setPosition(this->getPosition());
}

sf::Vector2f Bullet::normalize(const sf::Vector2f& vector) {

	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	if (length > 0) {
		return sf::Vector2f(vector.x / length, vector.y / length);
	}
	return sf::Vector2f(0.f, 0.f);
}

Bullet::~Bullet()
{
	this->setSprite(nullptr);
}

//--------------------//* BULLET MANAGER *\\--------------------\\

//* FUNCTIONS *\\


void BulletManager::checkCollisions(Entity* entity)
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet == nullptr) { index++;  continue; }

		if (bullet->collided(entity) && entity != bullet->getOwner())
		{
			float entityPoints = 0.f;

			Player* player = dynamic_cast<Player*>(entity);
			if (player) {
				if (player->isOnHitCooldown()) return;
				//std::cout << "-" << bullet->getDamage() << "HP\n";
			}
			else 
			{
				entityPoints = entity->getPoints();
			}

			entity->updateHealth(-(bullet->getDamage())); // -x hp

			if (entity->isDead() && !entity->isPlayer() && bullet->getOwner()->isPlayer())
			{
				Player* player_ = dynamic_cast<Player*>(bullet->getOwner());
				player_->updateScore(entityPoints);

				if (dynamic_cast<Boss*>(entity)) { LevelManager::getInstance()->levelCompleted = true; }
			}

			//delete
			bullet->setNullOwner();
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

Bullet* BulletManager::spawnBullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed)
{

	Bullet* newBullet = new Bullet(20, speed * WindowConfig::getInstance()->SIZE_X/192, position, direction);
	this->bullets.push_back(newBullet);
	newBullet->setOwner(owner);
	newBullet->setColor(owner->getColor());
	this->setSprites();
	return newBullet;

} 

Bullet* BulletManager::spawnBullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, BulletType bulletType, float speed)
{
	Bullet* newBullet = nullptr;

	switch (bulletType)
	{
	case DEFAULT_b: newBullet = new Bullet(20, speed * WindowConfig::getInstance()->SIZE_X / 192, position, direction);  break;
	case HOMING_b: newBullet = new HomingBullet(position, owner->getTarget(), {0, 0});  break;
	case DEFAULT_boss: newBullet = new DefaultBoss(position, direction);  break;
	case SHRIMP_boss: newBullet = new Shrimp(position, direction);  break;
	case PUFFER_boss: newBullet = new Puffer(position, direction, owner, owner->getTarget());  break;
	case HOMING_boss: newBullet = new HomingBulletBoss(position, owner->getTarget(), {0, 0});  break;
	}

	if (newBullet == nullptr)
	{
		std::cout << "CAN'T CREATE ENEMY OF TYPE " << std::to_string(bulletType) << '\n'; return spawnBullet(owner, position, direction, speed);
	}

	newBullet->setOwner(owner);
	this->bullets.push_back(newBullet);
	this->setSprites();
	return newBullet;
}

Bullet* BulletManager::spawnBullet(Entity* owner, sf::Vector2f position, sf::Vector2f direction, float speed, sf::Vector2f textureCoords)
{
		
	Bullet* newBullet = new Bullet(20, speed * WindowConfig::getInstance()->SIZE_X / 192, position, direction, textureCoords);
	this->bullets.push_back(newBullet);
	newBullet->setOwner(owner);
	newBullet->setColor(owner->getColor());
	this->setSprites();
	return newBullet;
}

void BulletManager::despawnBullets()
{
	unsigned index = 0;
	for (Bullet* bullet : this->bullets)
	{
		if (bullet == nullptr) { index++;  continue; }

		if (bullet->getPosition().x > WindowConfig::getInstance()->SIZE_X || bullet->getPosition().x < 0 || bullet->getLifeTime() >= bullet->getLifeTimeMax())
		{
			//delete
			bullet->setNullOwner();
			delete this->bullets.at(index);
			this->bullets.erase(this->bullets.begin() + index);
			index--;
		}
		index++;
	}
}

//* GRAPHICS *\\

bool BulletManager::loadTexture()
{
	if (!this->texture.loadFromFile("assets/textures/Bullets.png")) return false;
	this->setSprites();
	return true;
}

void BulletManager::setSprites()
{
	for (Bullet* adress : this->bullets)
{
		if (adress->getSprite() != nullptr) continue;

		sf::Sprite* sprite = new sf::Sprite;
		sprite->setTexture(this->texture);

		sprite->setScale({ adress->getHitbox().getSize().x * 2 / 35, adress->getHitbox().getSize().y * 2 / 35 });
		sprite->setOrigin({
			adress->getHitbox().getOrigin().y / sprite->getScale().y,
			adress->getHitbox().getOrigin().y / sprite->getScale().y
			});

		sprite->setTextureRect(sf::IntRect(
			adress->getTextureCoords().x * LevelManager::getInstance()->TILE_SIZE / 2,
			adress->getTextureCoords().y * LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2,
			LevelManager::getInstance()->TILE_SIZE / 2));

		adress->setSprite(sprite);
	}
}

void BulletManager::drawBullets(sf::RenderWindow& window)
{
	for (Bullet* adress : this->bullets)
	{
		if (!adress->getSprite()) continue;

		adress->getSprite()->setPosition(adress->getPosition());

		window.draw(*adress->getSprite());
	}
}

//* UPDATING *\\

void BulletManager::updatePositions(float deltaTime)
		{
	for (Bullet* adress : this->bullets)
			{
		adress->updatetLifeTime(deltaTime);
		if (adress == nullptr) { continue; }

		adress->updatePosition(deltaTime);
	}
}

void BulletManager::updateOwners(Entity* owner) //Updates null owners
{
	for (Bullet* adress : this->bullets)
	{
		if (adress == nullptr) { continue; }

		if (adress->getOwner() == owner)
		{
			adress->setNullOwner();
		}
	}
}
