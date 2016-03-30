#include "stdafx.h"
#include "Sounds.h"
#include <iostream>

static bool instanceFlag = false;
static Sounds* instance = NULL;
Sounds::Sounds()
{
	LoadSounds();
}


Sounds::~Sounds()
{
}
Sounds* Sounds::getInstance(){
	if (!instanceFlag)
	{
		instance = new Sounds();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void Sounds::LoadSounds()
{
	if (!menuBuffer.loadFromFile("../Assets/updown.ogg"))
	{
		std::cout << "Can't find Menu Sound" << std::endl;
	}
	
	if (!jumpBuffer.loadFromFile("../Assets/jump.ogg"))
	{
		std::cout << "Can't find jump Sound" << std::endl;
	}

	if (!deathBuffer.loadFromFile("../Assets/death.ogg"))
	{
		std::cout << "Can't find jump Sound" << std::endl;
	}

	if (!powerBuffer.loadFromFile("../Assets/Magic.ogg"))
	{
		std::cout << "Can't find jump Sound" << std::endl;
	}

	if (!pickupBuffer.loadFromFile("../Assets/pickup.ogg"))
	{
		std::cout << "Can't find jump Sound" << std::endl;
	}


	menuSound.setBuffer(menuBuffer);
	jumpSound.setBuffer(jumpBuffer);
	deathSound.setBuffer(deathBuffer);
	pickupSound.setBuffer(pickupBuffer);
	powerSound.setBuffer(powerBuffer);
	soundOn = false;
}

//////////////////////////////////////////////menu music//////////////////
void Sounds::playMenuMusic()
{
	if (!menuMusic.openFromFile("../Assets/MenuMusic.ogg"))
	{
		std::cout << "Can't find MenuMusic" << std::endl;
	}
	if (soundOn)
	{
		menuMusic.play();
		menuMusic.setLoop(true);
	}
}
void Sounds::stopMenuMusic()
{
	menuMusic.stop();

}
/////////////////////////////////////////////Level1 Music///////////////////
void Sounds::playLevel1Music()
{
	if (!level1Music.openFromFile("../Assets/level1.ogg"))
	{
		std::cout << "Can't find Level 1 Music" << std::endl;
	}
	if (soundOn)
	{
		level1Music.setVolume(30);
		level1Music.play();
		level1Music.setLoop(true);
	}
}
void Sounds::stopLevel1Music()
{
	level1Music.stop();
}
void Sounds::playMenuSound()
{
	if (soundOn)
	{
		menuSound.setVolume(100);
		menuSound.play();
	}
}
void Sounds::playJumpSound()
{
	if (soundOn)
	{
		jumpSound.setVolume(60);
		jumpSound.play();
	}
}


void Sounds::playPickupSound()
{
	if (soundOn)
	{
		pickupSound.setVolume(75);
		pickupSound.play();
	}
}
void Sounds::playPowerSound()
{
	if (soundOn)
	{
		powerSound.setVolume(100);
		powerSound.play();
		powerSound.setLoop(true);
	}
}
void Sounds::stopPowerSound()
{
	powerSound.stop();

}

void Sounds::playDeathSound()
{
	if (soundOn)
	{
		deathSound.setVolume(100);
		deathSound.play();
	}
}

