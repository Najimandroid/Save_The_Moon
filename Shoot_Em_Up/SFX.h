#pragma once

#include <SFML/Audio.hpp>
#include "Music.h"
#include <vector>
#include <iostream>

class SFXManager
{
private:
	static SFXManager* instance;

	std::vector<sf::Sound*> sounds;
	std::vector<sf::SoundBuffer*> buffers;

	SFXManager() {}
public:
	static SFXManager* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new SFXManager();
		}
		return instance;
	}

	sf::Sound* play(const std::string& bufferPath);
	void checkForDelete();
};