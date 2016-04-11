#include "stdafx.h"
#include "Menu.h"



Menu::Menu(RenderWindow* win):m_win(win)
{
	screenWidth = m_win->getView().getCenter().x * 2;
	screenHeight = m_win->getView().getCenter().y * 2;
	LoadAssets();
	selectedItemIndex = 0;

}


Menu::~Menu()
{
}
void Menu::LoadAssets()
{
	if (!font.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "Error while loading the font";
	}

	if (!buttonTexture.loadFromFile("../Assets/buttonStock.png"))
	{
		std::cout << "problem with loading the buttonStock.png" << std::endl;
	}
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		buttonSprite[i].setTexture(buttonTexture);
	}
	placeButtons();
}
void Menu::highLightButton()
{
	mousePos = m_win->mapPixelToCoords(sf::Mouse::getPosition(*m_win));
	
	if (!mouseClicked)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mouseClicked = true;

		}
	}
	else if (!Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClicked = false;
	}

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		if (mousePos.x >= buttonSprite[i].getPosition().x && mousePos.x <= buttonSprite[i].getPosition().x + buttonSprite[i].getGlobalBounds().width
			&& mousePos.y >= buttonSprite[i].getPosition().y && mousePos.y <= buttonSprite[i].getPosition().y + buttonSprite[i].getGlobalBounds().height)
		{
			menu[i].setColor(sf::Color(Color::Red));
			selectedItemIndex = i;

			if (mouseClicked)
			{
				if (i == 0)
				{
					std::cout << "game pressed" << std::endl;
					g_States->setState(GAME);
					Sounds::getInstance()->stopMenuMusic();
					Sounds::getInstance()->playLevel1Music();
				}
				else if (i == 1)
				{
					std::cout << "options pressed" << std::endl;
					g_States->setState(OPTIONS);
				}
				else
				{
					m_win->close();
				}
			}
			
		}
		else
		{
			if (i == selectedItemIndex)
			{
				menu[i].setColor(sf::Color(Color::Red));
			}
			else
			{
				menu[i].setColor(sf::Color(Color::White));
			}
		}
			
	}
}
void Menu::draw(sf::RenderWindow &win){

	highLightButton();
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
		
		win.draw(buttonSprite[i]);
		win.draw(menu[i]);
	}
}
void Menu::MoveUP()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::placeButtons()
{
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("PLAY GAME");
	menu[0].setPosition(sf::Vector2f(screenWidth - 250, screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 1));	
	//buttonSprite[0].setTextureRect(sf::IntRect(0, 0, 298, 81));
	buttonSprite[0].scale(sf::Vector2f(.8f, .6f));
	buttonSprite[0].setPosition(sf::Vector2f(screenWidth - 315, (screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 1) - 5.f));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("OPTIONS");
	menu[1].setPosition(sf::Vector2f(screenWidth - 240, screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	//buttonSprite[1].setTextureRect(sf::IntRect(0, 0, 298, 81));
	buttonSprite[1].setScale(sf::Vector2f(.8f, .6f));
	buttonSprite[1].setPosition(sf::Vector2f(screenWidth - 315, (screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 2) - 5.f));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("EXIT");
	menu[2].setPosition(sf::Vector2f(screenWidth - 220, screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	//buttonSprite[2].setTextureRect(sf::IntRect(0, 0, 298, 81));
	buttonSprite[2].setScale(sf::Vector2f(.8f, .6f));
	buttonSprite[2].setPosition(sf::Vector2f(screenWidth - 315, (screenHeight / (MAX_NUMBER_OF_ITEMS + 1) * 3) - 1.f));
}
