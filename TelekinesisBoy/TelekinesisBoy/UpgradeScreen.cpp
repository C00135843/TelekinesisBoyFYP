#include "stdafx.h"
#include "UpgradeScreen.h"
#include <iostream>


UpgradeScreen::UpgradeScreen(sf::RenderWindow* win) :m_win(win)
{
	noOfStars = 10;
	LoadAssets();
}


UpgradeScreen::~UpgradeScreen()
{
}


void UpgradeScreen::LoadAssets()
{
	if (!goldStar.loadFromFile("../Assets/starg.png"))
	{
		std::cout << "can't find goldstar " << std::endl;
	}
	g_Sprite.setTexture(goldStar);

	if (!blackStar.loadFromFile("../Assets/starb.png"))
	{
		std::cout << "cant find the black star" << std::endl;
	}
	b_sprite.setTexture(blackStar);

	if (!bgTexture.loadFromFile("../Assets/upgrade.png"))
	{
		std::cout << "cant find the background" << std::endl;
	}
	
	if (!f.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load";
	}
	

}
void UpgradeScreen::displayLivesAndScore()
{
	t.setFont(f);


}
void UpgradeScreen::displayEnduranceLevel()
{

}
void UpgradeScreen::displayNumberOfLives()
{

}

void UpgradeScreen::DisplayScreen()
{
	bg_Sprite.setTexture(bgTexture);
	bg_Sprite.setPosition(m_win->getView().getCenter().x -400, m_win->getView().getCenter().y - 300);
	bg_Sprite.setTextureRect(sf::IntRect(0, 0, m_win->getSize().x, m_win->getSize().y));
	m_win->draw(bg_Sprite);

}
