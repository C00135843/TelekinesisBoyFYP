#pragma once
#include "SFML/Graphics.hpp"

class UpgradeScreen
{
private:
	sf::Texture goldStar;
	sf::Texture blackStar;
	sf::Texture bgTexture;
	sf::Sprite bg_Sprite;
	sf::Sprite g_Sprite;
	sf::Sprite b_sprite;
	sf::Font f;
	sf::Text t;
	int noOfStars;
	sf::RenderWindow* m_win;
	void displayLivesAndScore();
	void displayEnduranceLevel();
	void displayNumberOfLives();
	void LoadAssets();
public:
	UpgradeScreen(sf::RenderWindow*);
	~UpgradeScreen();
	void DisplayScreen();
};

