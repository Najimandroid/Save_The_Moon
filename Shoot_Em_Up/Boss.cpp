#include "Boss.h"

//* CONSTRUCTOR *\\

Boss::Boss(sf::Vector2f position_)
{
	target = PlayerManager::getInstance()->getPlayers()[0];
	position = { position_.x, WindowConfig::getInstance()->SIZE_Y / 2.f };

	initHitbox({ WindowConfig::getInstance()->SIZE_Y / 2.5f, WindowConfig::getInstance()->SIZE_Y / 2.5f });
	initProperties(7500, 15, 1.5f, true, 4.f);

	textureCoords = { 0, 0 };
}

//* UPDATING *\\

void Boss::updatePosition(float deltaTime)
{
	LevelManager* levelManager = LevelManager::getInstance();
	if (this->active)
	{
		if (this->getPosition().x < WindowConfig::getInstance()->SIZE_X - this->hitbox.getSize().x / 2) //stay on the side
		{
			if (!healthBarSpawned) { HealthBarManager::getInstance()->createHealthBar(this->health)->linkEntity(this); healthBarSpawned = true; }

			velocity = { 0, (cos(x / 100) * (WindowConfig::getInstance()->SIZE_Y / 432*1.5f))}; // (WindowConfig::getInstance()->SIZE_Y / 54)
			x += 1.f;
		}
		else
		{
			velocity = { -levelManager->SCROLLING_SPEED * deltaTime * this->speed, 0 };
		}
	}
	else
	{
		velocity = { -levelManager->SCROLLING_SPEED * deltaTime, 0 };
	}
	this->position += velocity;
	this->hitbox.setPosition(this->position);
}

void Boss::updateShoot(float deltaTime)
{

	if (!this->isOnCooldown() && this->canShoot)
	{
		if (!this->active) return; //returns if not active

		//reset cooldown
		if (this->health <= 7500 / 2.f && !onRageMode) { shootCooldownMax /= 2.f; onRageMode = true; }
		this->shootCooldown = 0.f;

		std::function<void(Enemy*)> attack = attacks[rand() % attacks.size()];
		attack(this);
	}
	else
	{
		this->shootCooldown += deltaTime;
	}

}

//* ATTACKS *\\

void Attack_1(Enemy* entity)
{
	float offsetY = -1;
	for (float offset = -240; offset <= 240; offset += 240)
	{
		if (PlayerManager::getInstance()->getPlayers().empty()) { std::cout << "players empty\n"; return; }
		if (entity->getTarget() == nullptr) { std::cout << "huming error\n"; return; }

		BulletManager::getInstance()->spawnBullet(entity, { entity->getPosition().x, entity->getPosition().y - offset }, { -1, offsetY }, HOMING_boss, 2 * entity->getSpeed());
		offsetY += .33f;
	}

	std::cout << "attack 1\n";
	return;
}

void Attack_2(Enemy* entity)
{

	for (float offset = -240; offset <= 240; offset += 240)
	{
		BulletManager::getInstance()->spawnBullet(entity, { entity->getPosition().x, entity->getPosition().y - offset },
			entity->normalize(
				{
				  (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - entity->getPosition().x) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - entity->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - entity->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - entity->getPosition().y + offset) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - entity->getPosition().y + offset)))
				, (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - entity->getPosition().y + offset) / (sqrt((PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - entity->getPosition().x) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().x - entity->getPosition().x) + (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - entity->getPosition().y + offset) * (PlayerManager::getInstance()->getPlayers()[0]->getPosition().y - entity->getPosition().y + offset)))
				}
			),
			DEFAULT_boss,
			4 * entity->getSpeed());
	}

	std::cout << "attack 2\n";
	return;
}

void Attack_3(Entity* entity)
{

	for (float offsetY = -1; offsetY <= 1; offsetY += .4f)
	{
		BulletManager::getInstance()->spawnBullet(entity, entity->getPosition(), { -1, offsetY }, DEFAULT_boss, entity->getSpeed());
	}


	std::cout << "attack 3\n";
	return;
}