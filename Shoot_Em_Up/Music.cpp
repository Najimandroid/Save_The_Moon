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

void Music::Stop()
{
	music.stop();
}

void Music::UPVolume()
{
	volume += 10.f;  
	if (volume > 100.f) volume = 100.f;  
	music.setVolume(volume); 
}

void Music::DOWNVolume()
{
	volume -= 10.f;  
	if (volume < 0.f) volume = 0.f;  
	music.setVolume(volume); 
}

