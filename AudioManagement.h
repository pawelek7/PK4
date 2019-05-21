#ifndef AudioManagement_hpp
#define AudioManagement_hpp

#include <SFML/Audio/Music.hpp>

#include <vector>

class AudioManagement
{
	std::size_t index = 0;
	std::vector<std::string> playlist;

	sf::Music music;

public:
	AudioManagement() = default;
	virtual ~AudioManagement() = default;

	void UpdateAudio();

	void PlaySound(const std::string & path);
	void AddSoundToPlaylist(const std::string & path);

	float GetVelume() const;
	void SetVolume(float volumePower);
};

#endif // !AudioManagement_hpp
