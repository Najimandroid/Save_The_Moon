#pragma once
#include "Entity.h"
#include "Window.h"

#include  <SFML/Graphics.hpp>
#include <vector> 
#include <cmath>

class HealthBar 
{
private:

	float totalHealth;
	float remaingingHealth;

	Entity* linkedEntity;
	 
public:
	HealthBar(float health_): totalHealth(health_), remaingingHealth(health_), linkedEntity(nullptr) {}

	float getTotalHealth() { return ceil(totalHealth); };
	float getRemaingingHealth() { return ceil(remaingingHealth); }

	Entity* getEntity() { return linkedEntity; }

	void linkEntity(Entity* entity_) { linkedEntity = entity_; };

	void updateBar(float newHealth);
};


class HealthBarManager
{
private:
	static HealthBarManager* instance;

	std::vector<HealthBar*> bars;
public:

	static HealthBarManager* getInstance()
	{
		if (instance == nullptr) {
			instance = new HealthBarManager();
		}
		return instance;
	}

	std::vector<HealthBar*>& getBars() { return bars; }

	HealthBar* createHealthBar(float health);

	void updateBars();
	void drawBars(sf::RenderWindow& window);
};