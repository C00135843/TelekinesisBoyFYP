#include "stdafx.h"
#include "UpgradeScreen.h"
#include <iostream>


UpgradeScreen::UpgradeScreen(sf::RenderWindow* win) :m_win(win)
{
	noOfEnduranceStars = 5;
	noOfLivesStars = 5;
	livesSelected = 0;
	mouseX = 0;
	mouseY = 0;
	previousLivesSel = 0;
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
	//b_sprite.setTexture(blackStar);

	if (!bgTexture.loadFromFile("../Assets/upgrade.png"))
	{
		std::cout << "cant find the background" << std::endl;
	}
	
	if (!f.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load";
	}
	

}
void UpgradeScreen::displayLivesAndScore(Player *p)
{
	t.setFont(f);
	t.setCharacterSize(50);
	//scoreText.Bold;
	t.setString(std::string("TOTAL SCORE:\t") + std::to_string(p->getScore()));
	t.setPosition(m_win->getView().getCenter().x - 150, m_win->getView().getCenter().y - 250);
	m_win->draw(t);

	t.setFont(f);
	t.setCharacterSize(50);
	//scoreText.Bold;
	t.setString(std::string("TOTAL LIVES:\t\t") + std::to_string(p->getLives()));
	t.setPosition(m_win->getView().getCenter().x - 150, m_win->getView().getCenter().y - 150);
	m_win->draw(t);



}
void UpgradeScreen::displayEnduranceLevel(Player *p, Vector2f mousePos)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		mouseX = mousePos.x;
		mouseY = mousePos.y;
		mouseClicked = true;
	}
	else
	{
		mouseClicked = false;
	}


	int enduranceLevel = p->getEnduranceLevel();
	t.setFont(f);
	t.setCharacterSize(30);
	//scoreText.Bold;
	t.setString(std::string("ENDURANCE:\t\t") + std::to_string(enduranceLevel)+ "\t\t\tCOST 200 PER STAR");
	t.setPosition(m_win->getView().getCenter().x - 380, m_win->getView().getCenter().y - 50);
	m_win->draw(t);
	
	
	//int enduranceLevel = p->getEnduranceLevel();
	for (int i = 0; i < noOfEnduranceStars; i++)
	{
		if (i < enduranceLevel)
		{
			g_Sprite.setPosition(m_win->getView().getCenter().x - 300 + (i *100), m_win->getView().getCenter().y);
			g_Sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
			m_win->draw(g_Sprite);
		}
		else
		{
			b_sprite.setPosition(m_win->getView().getCenter().x - 300 + (i * 100), m_win->getView().getCenter().y);
			g_Sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
			m_win->draw(b_sprite);
		}

		if (mouseClicked&&(mouseX >= b_sprite.getPosition().x && mouseX <= b_sprite.getPosition().x +b_sprite.getTexture()->getSize().x &&
				mouseY >= b_sprite.getPosition().y && mouseY <= b_sprite.getPosition().y + b_sprite.getTexture()->getSize().y))
		{
			{
				std::cout << "Cost" + std::to_string(i + 1 - enduranceLevel) << std::endl;
				if (p->getScore() >= (i + 1 - enduranceLevel) * 200)
				{
					//p->increaseEnduranceLevel(i + 1);

					p->increaseEnduranceLevel(i + 1);
					p->decreaseScore((i + 1 - enduranceLevel) * 200);
					//break;


				}
				
			}

		}


	}
}
void UpgradeScreen::displayNumberOfLives(Player *p, Vector2f mousePos)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		mouseX = mousePos.x;
		mouseY = mousePos.y;
		mouseClicked = true;
	}
	else
	{
		mouseClicked = false;
	}
	t.setFont(f);
	t.setCharacterSize(30);
	//scoreText.Bold;
	t.setString(std::string("LIVES:\t\t") + std::to_string(livesSelected) + "\t\t\tCOST 350 PER STAR");
	t.setPosition(m_win->getView().getCenter().x - 380, m_win->getView().getCenter().y +75);
	m_win->draw(t);

	for (int i = 0; i < noOfLivesStars; i++)
	{
		if (i < livesSelected)
		{
			g_Sprite.setPosition(m_win->getView().getCenter().x - 300 + (i * 100), m_win->getView().getCenter().y + 125);
			g_Sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
			m_win->draw(g_Sprite);
		}
		else
		{
			b_sprite.setPosition(m_win->getView().getCenter().x - 300 + (i * 100), m_win->getView().getCenter().y + 125);
			b_sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
			m_win->draw(b_sprite);
		}
		if (mouseClicked && (mouseX >= b_sprite.getPosition().x && mouseX <= b_sprite.getPosition().x + b_sprite.getTexture()->getSize().x &&
			mouseY >= b_sprite.getPosition().y && mouseY <= b_sprite.getPosition().y + b_sprite.getTexture()->getSize().y))
		{
			{
				if (p->getScore() >= (i + 1 - livesSelected) * 350)
				{
					//p->decreaseScore(livesSelected * 350);
					previousLivesSel = livesSelected;
					livesSelected = i+1;
					p->decreaseScore((livesSelected - previousLivesSel) * 350);
					p->increaseLives(livesSelected - previousLivesSel);
					
					
				}

			}

		}

	}
}

void UpgradeScreen::UpdateStars(Vector2f mousePos)
{
	//if (Mouse::isButtonPressed(Mouse::Left)) {
	//	mouseX = mousePos.x;
	//	mouseY = mousePos.y;
	//	mouseClicked = true;
	//}
	//else
	//{
	//	mouseClicked = false;
	//}

	//for (int i = 0; i < noOfEnduranceStars; i++)
	//{

	//}
	//if (mouseClicked
	//	&& (mouseX >= b_sprite.getPosition().x && mouseX <= b_sprite.getPosition().x +b_sprite.getTexture()->getSize().x &&
	//		mouseY >= b_sprite.getPosition().y && mouseY <= b_sprite.getPosition().y + b_sprite.getTexture()->getSize().y))
	//{

	//}

}

void UpgradeScreen::DisplayScreen(Player *p, Vector2f mousePos)
{
	//bgTexture.
	bg_Sprite.setTexture(bgTexture);
	bg_Sprite.setPosition(m_win->getView().getCenter().x -400, m_win->getView().getCenter().y - 300);
	bg_Sprite.setTextureRect(sf::IntRect(0, 0, m_win->getSize().x, m_win->getSize().y));
	bg_Sprite.setColor(sf::Color(255, 255, 255, 128)); // halftransparent
	m_win->draw(bg_Sprite);

	displayLivesAndScore(p);
	displayEnduranceLevel(p, mousePos);
	displayNumberOfLives(p,mousePos);

}
