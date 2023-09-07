#include "Audio.h"

Audio::Audio()
{
	if (!menuBackgroundMusic.openFromFile("resources/music&sounds/my-trip-153903.wav"))
	{
		std::cout << "Error - menu background music" << std::endl;
	}
	menuBackgroundMusic.setLoop(true);

	/*if (!gameBackgroundMusic.openFromFile("resources/music&sounds/!!!!!!!!!!.wav"))
	{
		std::cout << "Error - game background music" << std::endl;
	}
	gameBackgroundMusic.setLoop(true);*/

	if (!buttonsSoundBuffer.loadFromFile("resources/music&sounds/menu-button-88360.wav"))
	{
		std::cout << "Error - sound" << std::endl;
	}
	buttonsSound.setBuffer(buttonsSoundBuffer);

	Update();
}

void Audio::Update()
{
	file.open("options.dat", std::ios_base::in | std::ios_base::binary);
	if (file.is_open())
	{
		optionsFromFile.reserve(NUMBER_OF_OPTIONS);
		for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
		{
			file.read((char*)&optionsFromFile[i], sizeof(std::pair<optionsTypes, int>));
		}
		file.close();
	}

	for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
	{
		if (optionsFromFile[i].first == music1)
		{
			if (optionsFromFile[i].second == 0)
			{
				enableMusic = false;
				menuBackgroundMusic.stop();
				//gameBackgroundMusic.stop();
			}
			else
			{
				enableMusic = true;
			}
		}
		else if (optionsFromFile[i].first == sounds1)
		{
			if (optionsFromFile[i].second == 0)
			{
				enableSounds = false;
			}
			else
			{
				enableSounds = true;
			}
		}

		if (optionsFromFile[i].first == music2)
		{
			musicVolume = optionsFromFile[i].second;
		}
		else if (optionsFromFile[i].first == sounds2)
		{
			soundVolume = optionsFromFile[i].second;
		}
	}

	menuBackgroundMusic.setVolume(musicVolume);
	//gameBackgroundMusic.setVolume(musicVolume);
	buttonsSound.setVolume(soundVolume);
}

void Audio::PlayMusic(bool menuMusic)
{
	if (enableMusic)
	{
		if (menuMusic)
		{
			menuBackgroundMusic.play();
		}
		else
		{
			//gameBackgroundMusic.play();
		}
	}
}

void Audio::PlaySound()
{
	if (enableSounds)
	{
		buttonsSound.play();
	}
}

int& Audio::GetMusicVolume()
{
	return musicVolume;
}

int& Audio::GetSoundVolume()
{
	return soundVolume;
}