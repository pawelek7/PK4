#ifndef AudioManagement_hpp
#define AudioManagement_hpp

#include <SFML/Audio/Music.hpp>

#include <vector>

#include "NoCopyNoMove.h"
/*
Class responsible for handling in-game music.

@author
Pawel Salicki
*/

class AudioManagement : public NoCopyNoMove
{
	std::size_t index = 0; //index of music container
	std::vector<std::string> playlist; //container that stores music

	sf::Music music; //music object from SFML library

public:
	AudioManagement() = default; //non-parametric constructor
	virtual ~AudioManagement() = default; //destructor

	void UpdateAudio(); //updating music

	void PlaySound(const std::string & path); //playing sound based on path
	void AddSoundToPlaylist(const std::string & path); //adding sound to container of playlist

	//setters
	void SetVolume(float volumePower);

	//getters
	float GetVelume() const;
};

#endif // !AudioManagement_hpp