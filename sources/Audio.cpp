#include "Audio.h"

Audio::Audio()
{
	if (!backgroundMusic.openFromFile("resources/music&sounds/my-trip-153903.wav"))
	{
		std::cout << "Error - background music" << std::endl;
		musicFileExist = false;
	}
	else
	{
		backgroundMusic.setLoop(true);
	}

	if (!buttonsSoundBuffer.loadFromFile("resources/music&sounds/menu-button-88360.wav"))
	{
		std::cout << "Error - sound" << std::endl;
		soundFileExist = false;
	}
	else
	{
		buttonsSound.setBuffer(buttonsSoundBuffer);
	}

	Update();
}

void Audio::Update()
{
	if (musicFileExist)
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

			for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
			{
				if (optionsFromFile[i].first == music1)
				{
					if (optionsFromFile[i].second == 0)
					{
						enableMusic = false;
						backgroundMusic.stop();
					}
					else
					{
						enableMusic = true;
					}
				}

				if (optionsFromFile[i].first == music2)
				{
					musicVolume = optionsFromFile[i].second;
				}
			}
		}
		backgroundMusic.setVolume(musicVolume);
	}

	if (soundFileExist)
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

			for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
			{
				if (optionsFromFile[i].first == sounds1)
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

				if (optionsFromFile[i].first == sounds2)
				{
					soundVolume = optionsFromFile[i].second;
				}
			}
		}
		buttonsSound.setVolume(soundVolume);
	}
}

void Audio::PlayMusic()
{
	if (enableMusic && musicFileExist)
	{
		backgroundMusic.play();
	}
}

void Audio::StopMusic()
{
	if (enableMusic && musicFileExist)
	{
		backgroundMusic.stop();
	}
}

void Audio::PlaySound()
{
	if (enableSounds && soundFileExist)
	{
		buttonsSound.play();
	}
}

int Audio::GetMusicVolume()
{
	return musicVolume;
}

int Audio::GetSoundVolume()
{
	return soundVolume;
}