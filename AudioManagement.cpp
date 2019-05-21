#include "AudioManagement.h"

#pragma region Class_Methods

void AudioManagement::UpdateAudio()
{
	if (this->music.getStatus() == sf::Music::Stopped && !this->playlist.empty())
	{
		this->index = (this->index + 1) % this->playlist.size();
		this->PlaySound(this->playlist[this->index]);
	}
}

void AudioManagement::PlaySound(const std::string & path)
{
	this->music.openFromFile(path);
	this->music.play();
}

void AudioManagement::AddSoundToPlaylist(const std::string & path)
{
	this->playlist.push_back(path);
}

#pragma endregion

#pragma region Setters

void AudioManagement::SetVolume(float volumePower)
{
	this->music.setVolume(volumePower);
}

#pragma endregion

#pragma region Getters

float AudioManagement::GetVelume() const
{
	return this->music.getVolume();
}

#pragma endregion