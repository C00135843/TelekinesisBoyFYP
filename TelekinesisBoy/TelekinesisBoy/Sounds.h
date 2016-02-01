#pragma once
#include <SFML/Audio/Listener.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>
class Sounds
{
private:
	Sounds();
	~Sounds();
	sf::SoundBuffer menuBuffer;
	sf::SoundBuffer jumpBuffer;
	sf::Music menuMusic;
	sf::Music level1Music;
	sf::Sound menuSound;
	sf::Sound jumpSound;
	
public:
	static Sounds* getInstance();
	void playMenuMusic();
	void stopMenuMusic();
	void playLevel1Music();
	void stopLevel1Music();
	void LoadSounds();
	void playMenuSound();
	void playJumpSound();

};

