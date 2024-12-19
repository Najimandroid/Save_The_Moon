#include "Music.h"
#include <iostream>



void Music::SetSound(const std::string& fichierMusique)
{
	if (!music.openFromFile(fichierMusique)) {
		std::cerr << "Erreur de chargement de la musique : " << fichierMusique << std::endl;
		return;
	}
	music.play();
	music.setVolume(volume);
	music.setLoop(true);
}

void Music::mute()
{
	if (isMuted) return;
	isMuted = true;
	stockedVolume = volume;
	music.setVolume(0.f);
}

void Music::demute()
{
	if (!isMuted) return;

	music.setVolume(stockedVolume);
	isMuted = false;
}

void Music::UPVolume()
{
	if (isMuted) return;
	volume += 1.f;  
	if (volume > 20.f) volume = 20.f;  
	music.setVolume(volume); 
}

void Music::DOWNVolume()
{
	if (isMuted) return;
	volume -= 1.f;  
	if (volume < 0.f) volume = 0.f;  
	music.setVolume(volume); 
}

