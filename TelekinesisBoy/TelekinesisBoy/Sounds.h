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
	sf::SoundBuffer deathBuffer;
	sf::SoundBuffer pickupBuffer;
	sf::SoundBuffer powerBuffer;
	//sf::SoundBuffer jumpBuffer;
	sf::Music menuMusic;
	sf::Music level1Music;
	sf::Sound menuSound;
	sf::Sound jumpSound;
	sf::Sound deathSound;
	sf::Sound pickupSound;
	sf::Sound powerSound;

	bool soundOn;
	
public:
	static Sounds* getInstance();
	void playMenuMusic();
	void stopMenuMusic();
	void playLevel1Music();
	void stopLevel1Music();
	void LoadSounds();
	void playMenuSound();
	void playJumpSound();
	void playDeathSound();
	void playPickupSound();
	void playPowerSound();
	void stopPowerSound();
	void setSound(bool s){ soundOn = s; }
	bool getSound(){ return soundOn; }

};

