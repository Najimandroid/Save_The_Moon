#include "HealthBar.h"

#include  <SFML/Graphics.hpp>
#include <vector> 
#include <cmath>

void HealthBar::updateBar(float newHealth)
{
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
	for (HealthBar* bar : this->bars)
	{
		bar->updateBar(bar->getEntity()->getHealth());
	}
}

void HealthBarManager::drawBars(sf::RenderWindow& window)
{

	for (HealthBar* bar : this->bars)
	{
		sf::RectangleShape background_(sf::Vector2f(300, 40));
		background_.setFillColor(sf::Color::Red);
		background_.setPosition({ 300, 40 });
		window.draw(background_);

		sf::RectangleShape body_;
		float healthBarSizeX = ((bar->getRemaingingHealth() * bar->getTotalHealth()) / 100) * (background_.getSize().x/100);

		if (healthBarSizeX <= 0) { body_.setSize(sf::Vector2f(0, 40)); }
		else{ body_.setSize(sf::Vector2f(healthBarSizeX, 40)); }
		
		body_.setFillColor(sf::Color::Green);
		body_.setPosition({ 300, 40 });
		window.draw(body_);
	}

}