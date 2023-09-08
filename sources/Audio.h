#pragma once
#include <fstream>
#include <SFML/Audio.hpp>
#include "Definitions.h"
#include <iostream>

class Audio
{
private:
	std::fstream file;
	std::vector<std::pair<optionsTypes, int>> optionsFromFile;

	sf::SoundBuffer buttonsSoundBuffer;
	sf::Sound buttonsSound;

	sf::Music backgroundMusic;

	bool enableSounds = true;
	bool enableMusic = true;

	int musicVolume = 40;
	int soundVolume = 40;

public:
	Audio();

	void Update();

	void PlayMusic();
	void StopMusic();
	void PlaySound();

	int& GetMusicVolume();
	int& GetSoundVolume();
};