#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "GameStates.h"
#include "Sounds.h"
#define MAX_NUMBER_OF_ITEMS 3

using namespace sf;
class Menu
{
public:
	Menu(sf::RenderWindow *window);
	~Menu();
	void LoadAssets();
	void highLightButton();
	void draw(sf::RenderWindow &window);
	void MoveUP();
	void MoveDown();
	void placeButtons();
	int GetPressedItem(){ return selectedItemIndex; }

private:
	int selectedItemIndex;
	bool mouseClicked = false;
	sf::Vector2f mousePos;
	float screenWidth, screenHeight;
	sf::RenderWindow *m_win;
	sf::Font font;
	sf::Texture buttonTexture;
	Sounds* s_Sound = Sounds::getInstance();
	GameStates* g_States = GameStates::getInstance();
	sf::Sprite buttonSprite[MAX_NUMBER_OF_ITEMS];
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};

