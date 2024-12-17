#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>


class Music
{
private:
	sf::Music music;
public:
	float volume = 100.f;
	void SetSound(const std::string& fichierMusique);
	void Stop();
	void UPVolume();
	void DOWNVolume();
};