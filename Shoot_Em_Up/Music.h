#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


class Music
{
private:
	static Music* instance;
	
	sf::Music music;
	float stockedVolume;

	bool isMuted;

	Music() { stockedVolume = 0.f; isMuted = false; }
public:
	static Music* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Music();
		}
		return instance;
	}

	float volume = 10.f;
	void SetSound(const std::string& fichierMusique);

	void mute();
	void demute();

	void UPVolume();
	void DOWNVolume();
};