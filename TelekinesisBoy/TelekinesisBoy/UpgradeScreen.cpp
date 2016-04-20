#include "stdafx.h"
#include "UpgradeScreen.h"
#include <iostream>


UpgradeScreen::UpgradeScreen(sf::RenderWindow* win) :m_win(win)
{
	p = playerInfo::getInstance();
	levelManager = LevelManager::getInstance(m_win);
	noOfEnduranceStars = 5;
	noOfLivesStars = 5;
	originalScore = p->getScore();
	originalEndurance = p->getEnduranceLevel();
	originalLives = p->getLives();
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
	

	if (!blackStar.loadFromFile("../Assets/starb.png"))
	{
		std::cout << "cant find the black star" << std::endl;
	}
	if (!bgTexture.loadFromFile("../Assets/upgrade.png"))
	{
		std::cout << "cant find the background" << std::endl;
	}
	
	if (!f.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load";
	}
	if (!buttonTexture.loadFromFile("../Assets/buttonStock.png"))
	{
		std::cout << "cant find the buttonStock.png " << std::endl;
	}
	for (int i = 0; i < noOfEnduranceStars; i++)
	{
		lives_sprite[i].setTexture(blackStar);
		Endurance_sprite[i].setTexture(blackStar);
	}
	displayEnduranceLevel();
	displayNumberOfLives();

}
void UpgradeScreen::displayLivesAndScore(Vector2f mousePos)
{
	originalScore = p->getScore();
	mouseX = mousePos.x;
	mouseY = mousePos.y;
	if (!mouseClicked)
	{
		if (Mouse::isButtonPressed(Mouse::Left)) {

			mouseClicked = true;
		}
	}
	else if (!Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = false;
	}
	t.setFont(f);
	t.setCharacterSize(50);
	//scoreText.Bold;
	t.setString(std::string("TOTAL SCORE:\t") + std::to_string(p->getScore()));
	t.setPosition(m_win->getView().getCenter().x - 200, m_win->getView().getCenter().y - 250);
	m_win->draw(t);

	t.setFont(f);
	t.setCharacterSize(50);
	//scoreText.Bold;
	t.setString(std::string("TOTAL LIVES:\t\t") + std::to_string(p->getLives()));
	t.setPosition(m_win->getView().getCenter().x - 200, m_win->getView().getCenter().y - 150);
	m_win->draw(t);

	for (int i = 0; i < 3; i++)
	{
		buttonSprite[i].setTexture(buttonTexture);
		buttonSprite[i].setScale(.5f, .6f);
		if (i == 0)
		{
			buttonSprite[i].setPosition(m_win->getView().getCenter().x+220 , m_win->getView().getCenter().y+13);
		}
		else if (i == 1)
		{
			buttonSprite[i].setPosition(m_win->getView().getCenter().x + 220, m_win->getView().getCenter().y + 137);
		}
		else
			buttonSprite[i].setPosition(m_win->getView().getCenter().x - 40, m_win->getView().getCenter().y + 225);
		m_win->draw(buttonSprite[i]);

		if (mousePos.x >= buttonSprite[i].getPosition().x && mousePos.x <= buttonSprite[i].getPosition().x + buttonSprite[i].getGlobalBounds().width
			&& mousePos.y >= buttonSprite[i].getPosition().y && mousePos.y <= buttonSprite[i].getPosition().y + buttonSprite[i].getGlobalBounds().height)
		{
			if (mouseClicked)
			{
				std::cout << "button" << std::endl;
				
				if (i == 0)
				{
					Sounds::getInstance()->playMenuSound();
					p->setScore(p->getOrginalScore());
					p->increaseEnduranceLevel(p->getOriginalEnduranceLevel());
				}
				else if (i == 1)
				{
					Sounds::getInstance()->playMenuSound();
					p->setScore(p->getOrginalScore());
					p->setLives(p->getOriginalLives());
					livesSelected = 0;
				}
				else
				{
					levelManager->Level1Del();
					levelManager->Level2Load();
					if (levelManager->getLevel() < 2)
					{
						Sounds::getInstance()->stopMenuMusic();
						Sounds::getInstance()->playLevel1Music();
						levelManager->increaseLevel();
						g_States->setState(GAME);
					}
					else
						g_States->setState(END);
				}
				
			}
		}


	}
	


	t.setCharacterSize(20);
	t.setColor(sf::Color::White);
	t.setString(std::string("CLEAR"));
	t.setPosition(m_win->getView().getCenter().x + 275, m_win->getView().getCenter().y+25 );
	m_win->draw(t);

	t.setPosition(m_win->getView().getCenter().x + 275, m_win->getView().getCenter().y + 150);
	m_win->draw(t);

	t.setString(std::string("FINISH"));
	t.setPosition(m_win->getView().getCenter().x + 15, m_win->getView().getCenter().y + 235);
	m_win->draw(t);


}
void UpgradeScreen::displayEnduranceLevel()
{

	int enduranceLevel = p->getEnduranceLevel();
	t.setFont(f);
	t.setCharacterSize(30);
	//scoreText.Bold;
	t.setString(std::string("ENDURANCE:\t\t") + std::to_string(enduranceLevel)+ "\t\t\tCOST 200 PER STAR");
	t.setPosition(m_win->getView().getCenter().x - 380, m_win->getView().getCenter().y - 50);
	m_win->draw(t);
	

	for (int i = 0; i < noOfEnduranceStars; i++)
	{
		if (i < enduranceLevel)
		{
			Endurance_sprite[i].setTexture(goldStar);
		}
		else
		{
			Endurance_sprite[i].setTexture(blackStar);

		}
		Endurance_sprite[i].setPosition(m_win->getView().getCenter().x - 300 + (i * 100), m_win->getView().getCenter().y);
		Endurance_sprite[i].setTextureRect(sf::IntRect(0, 0, 60, 60));
		m_win->draw(Endurance_sprite[i]);

	}

}
void UpgradeScreen::displayNumberOfLives()
{

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
			lives_sprite[i].setTexture(goldStar);
		}
		else
		{
			lives_sprite[i].setTexture(blackStar);
		}
		lives_sprite[i].setPosition(m_win->getView().getCenter().x - 300 + (i * 100), m_win->getView().getCenter().y + 125);
		lives_sprite[i].setTextureRect(sf::IntRect(0, 0, 60, 60));
		m_win->draw(lives_sprite[i]);
	}
}

void UpgradeScreen::UpdateStars(Vector2f mousePos)
{
	mouseX = mousePos.x;
	mouseY = mousePos.y;
	if (Mouse::isButtonPressed(Mouse::Left)) {

		mouseClicked = true;
	}
	else if (!Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = false;
	}
	int enduranceLevel = p->getEnduranceLevel();
	for (int i = 0; i < noOfEnduranceStars; i++)
	{
		if (mouseX >= Endurance_sprite[i].getGlobalBounds().left && mouseX <= Endurance_sprite[i].getGlobalBounds().left + Endurance_sprite[i].getGlobalBounds().width
			&& mouseY >= Endurance_sprite[i].getGlobalBounds().top && mouseY <= Endurance_sprite[i].getGlobalBounds().top + Endurance_sprite[i].getGlobalBounds().height)
		{
			if (mouseClicked)
			{
				if (enduranceLevel < i + 1)
				{
					int costOfupgrade = ((i + 1) - enduranceLevel) * COST_OF_UPGRADE;
					if (p->getScore() >= costOfupgrade)
					{
						Sounds::getInstance()->playMenuSound();
						p->decreaseScore(costOfupgrade);
						p->increaseEnduranceLevel(i + 1);
					}

				}
				
			}
		}
	}
	for (int i = 0; i < noOfLivesStars; i++)
	{
		if (mouseX >= lives_sprite[i].getGlobalBounds().left && mouseX <= lives_sprite[i].getGlobalBounds().left + lives_sprite[i].getGlobalBounds().width
			&& mouseY >= lives_sprite[i].getGlobalBounds().top && mouseY <= lives_sprite[i].getGlobalBounds().top + lives_sprite[i].getGlobalBounds().height)
		{
			if (mouseClicked)
			{
				if (livesSelected < i + 1)
				{
					int costOflife = ((i + 1) - livesSelected) * COST_OF_LIVES;
					if (p->getScore() >= costOflife)
					{
						Sounds::getInstance()->playMenuSound();
						previousLivesSel = livesSelected;
						livesSelected = i + 1;
						p->decreaseScore(costOflife);
						p->increaseLives(livesSelected - previousLivesSel);
					}

				}

			}
		}
	}

}

void UpgradeScreen::DisplayScreen(Vector2f mousePos)
{
	//bgTexture.
	bg_Sprite.setTexture(bgTexture);
	bg_Sprite.setPosition(m_win->getView().getCenter().x -400, m_win->getView().getCenter().y - 300);
	bg_Sprite.setTextureRect(sf::IntRect(0, 0, m_win->getSize().x, m_win->getSize().y));
	bg_Sprite.setColor(sf::Color(255, 255, 255, 128)); // halftransparent
	m_win->draw(bg_Sprite);
	
	displayLivesAndScore(mousePos);
	displayEnduranceLevel();
	displayNumberOfLives();
	UpdateStars(mousePos);

}
