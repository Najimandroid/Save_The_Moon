#include "SFX.h"

sf::Sound* SFXManager::play(const std::string& bufferPath)
{

	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	sf::Sound* sound = new sf::Sound;

	if (!buffer->loadFromFile(bufferPath))
	{
		std::cout << "Couldn't load sound effect: " << bufferPath << std::endl;
		delete buffer;
		delete sound;
		return sound;
	}

	this->buffers.push_back(buffer);

	
	sound->setBuffer(*buffer);

	sound->setVolume(Music::getInstance()->volume);
	if(bufferPath == "assets/sfx/Shoot.mp3") sound->setVolume(Music::getInstance()->volume/2.f);
	

	sound->play();

	this->sounds.push_back(sound);
	return sound;
}

void SFXManager::checkForDelete()
{
	unsigned index = 0;
	for (sf::Sound* sound : this->sounds)
	{
		if (sound == nullptr) { index++;  continue; }

		if (sound->getStatus() == sf::SoundSource::Stopped)
		{
			delete this->sounds.at(index);
			this->sounds.erase(this->sounds.begin() + index);
			delete this->buffers.at(index);
			this->buffers.erase(this->buffers.begin() + index);
			index--;
		}
		index++;
	}
}
