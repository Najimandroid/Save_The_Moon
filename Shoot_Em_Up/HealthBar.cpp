#include "HealthBar.h"
#include "Window.h"

#include  <SFML/Graphics.hpp>
#include <vector> 
#include <iostream>
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
	float offset = 0;
	for (HealthBar* bar : this->bars)
	{
		sf::RectangleShape background_(sf::Vector2f(WindowConfig::getInstance()->SIZE_X/5, WindowConfig::getInstance()->SIZE_Y/16));
		background_.setFillColor(sf::Color::Red);
		background_.setPosition({ 300 + 800 * offset, 40 });
		window.draw(background_);

		sf::RectangleShape body_;
		std::cout << "remainging: " << bar->getRemaingingHealth() << "\ntotal: " << bar->getTotalHealth() << "\npercent: " << (bar->getRemaingingHealth() / bar->getTotalHealth() * 100) << "\nbar size: " << (background_.getSize().x) * (bar->getRemaingingHealth() / bar->getTotalHealth() * 100) << std::endl;
		float healthBarSizeX = float(background_.getSize().x) * (bar->getRemaingingHealth() / bar->getTotalHealth());

		if (healthBarSizeX <= 0) { body_.setSize(sf::Vector2f(0, 40)); }
		else{ body_.setSize(sf::Vector2f(healthBarSizeX, WindowConfig::getInstance()->SIZE_Y / 16)); }
		
		body_.setFillColor(sf::Color::Green);
		body_.setPosition({ 300 + 800 * offset, 40 });
		window.draw(body_);

		offset++;
	}

}