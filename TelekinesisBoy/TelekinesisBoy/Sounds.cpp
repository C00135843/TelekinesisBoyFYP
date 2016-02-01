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
	menuSound.setBuffer(menuBuffer);
	if (!jumpBuffer.loadFromFile("../Assets/jump.ogg"))
	{
		std::cout << "Can't find jump Sound" << std::endl;
	}
	jumpSound.setBuffer(jumpBuffer);
}

//////////////////////////////////////////////menu music//////////////////
void Sounds::playMenuMusic()
{
	if (!menuMusic.openFromFile("../Assets/MenuMusic.ogg"))
	{
		std::cout << "Can't find MenuMusic" << std::endl;
	}
	menuMusic.play();
	menuMusic.setLoop(true);
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
	level1Music.play();
	level1Music.setLoop(true);
}
void Sounds::stopLevel1Music()
{
	level1Music.stop();
}
void Sounds::playMenuSound()
{
	menuSound.setVolume(100);
	menuSound.play();
}
void Sounds::playJumpSound()
{
	jumpSound.setVolume(60);
	jumpSound.play();
}

