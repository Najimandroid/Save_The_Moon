#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


class Music
{
private:
	static Music* instance;
	Music() {}
	sf::Music music;
public:
	static Music* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new Music();
		}
		return instance;
	}

	float volume = 100.f;
	void SetSound(const std::string& fichierMusique);

	void mute();
	void demute();

	void UPVolume();
	void DOWNVolume();
};