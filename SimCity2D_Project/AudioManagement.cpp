#include "AudioManagement.h"

#pragma region Class_Methods

#pragma region Description of the method

/*
A method that updates the music being played.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void AudioManagement::UpdateAudio()
{
	//if music is stopped and playlist isn't empty play next music from playlist
	if (this->music.getStatus() == sf::Music::Stopped && !this->playlist.empty())
	{
		this->index = (this->index + 1) % this->playlist.size();
		this->PlaySound(this->playlist[this->index]);
	}
}

#pragma region Description of the method

/*
A method that plays the given music from the specified file path.

method parameters:
____________________
path - path to music file

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void AudioManagement::PlaySound(const std::string & path)
{
	this->music.openFromFile(path);
	this->music.play();
}

#pragma region Description of the method

/*
A method that adds music to a playlist.

method parameters:
____________________
path - path to music file

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void AudioManagement::AddSoundToPlaylist(const std::string & path)
{
	this->playlist.push_back(path);
}

#pragma endregion

#pragma region Setters
//setters

void AudioManagement::SetVolume(float volumePower)
{
	this->music.setVolume(volumePower);
}

#pragma endregion

#pragma region Getters
//getters

float AudioManagement::GetVelume() const
{
	return this->music.getVolume();
}

#pragma endregion