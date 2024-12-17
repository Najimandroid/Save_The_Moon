#include "HealthBar.h"

void HealthBar::updateBar(float newHealth)
{
	if (this->getEntity() == nullptr) { remaingingHealth = 0; return; }
	this->remaingingHealth = newHealth;
}

HealthBar* HealthBarManager::createHealthBar(float health_)
{
	HealthBar* newBar = new HealthBar(health_);
	this->bars.push_back(newBar);
	return newBar;
}

void HealthBarManager::updateBars()
{
	//delete
	for (auto it = this->bars.begin(); it != this->bars.end(); )
	{
		HealthBar* bar = *it;
		//std::cout << enemy->getHealth() << ", ";

		if (bar->getRemaingingHealth() <= 0) {
			// delete if bar's entity is dead
			delete bar;
			it = this->bars.erase(it);
		}
		else {
			++it;  // updates only if the enemy is deleted
		}
	}

	for (HealthBar* bar : this->bars)
	{
		if (!bar->getEntity()) { continue; }
		bar->updateBar(bar->getEntity()->getHealth());
	}
}

void HealthBarManager::drawBars(sf::RenderWindow& window)
{
	float offset = 0;
	for (HealthBar* bar : this->bars)
	{
		if (bar->getEntity() == nullptr) { continue; }

		sf::RectangleShape background_(sf::Vector2f(WindowConfig::getInstance()->SIZE_X/5, WindowConfig::getInstance()->SIZE_Y/16));
		background_.setFillColor(sf::Color::Red);
		background_.setPosition({ 300 + 800 * offset, 40 });
		window.draw(background_);

		sf::RectangleShape body_;
		//std::cout << "remainging: " << bar->getRemaingingHealth() << "\ntotal: " << bar->getTotalHealth() << "\npercent: " << (bar->getRemaingingHealth() / bar->getTotalHealth() * 100) << "\nbar size: " << (background_.getSize().x) * (bar->getRemaingingHealth() / bar->getTotalHealth() * 100) << std::endl;
		float healthBarSizeX = float(background_.getSize().x) * (bar->getRemaingingHealth() / bar->getTotalHealth());

		if (healthBarSizeX <= 0) { body_.setSize(sf::Vector2f(0, 40)); }
		else{ body_.setSize(sf::Vector2f(healthBarSizeX, WindowConfig::getInstance()->SIZE_Y / 16)); }
		
		body_.setFillColor(sf::Color::Green);
		body_.setPosition({ 300 + 800 * offset, 40 });
		window.draw(body_);

		offset++;
	}

}