#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class UpgradeScreen
{
private:
	sf::Texture goldStar;
	sf::Texture blackStar;
	sf::Texture bgTexture;
	sf::Sprite bg_Sprite;
	sf::Sprite g_Sprite;
	sf::Sprite bl_sprite;
	sf::Sprite b_sprite;
	sf::Font f;
	sf::Text t;
	int mouseX;
	int mouseY;
	bool mouseClicked;
	int noOfEnduranceStars;
	int noOfLivesStars;
	int livesSelected;
	int previousLivesSel;
	sf::RenderWindow* m_win;
	void displayLivesAndScore(Player *p);
	void displayEnduranceLevel(Player *p, Vector2f mousePos);
	void displayNumberOfLives(Player *p, Vector2f mousePos);
	void LoadAssets();
public:
	UpgradeScreen(sf::RenderWindow*);
	~UpgradeScreen();
	void UpdateStars(Vector2f mousePos);
	void DisplayScreen(Player *p, Vector2f mousePos);
};

