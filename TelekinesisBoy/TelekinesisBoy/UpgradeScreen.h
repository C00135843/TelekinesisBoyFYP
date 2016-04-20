#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "GameStates.h"
#include "Sounds.h"
#include "LevelManager.h"
#include "playerInfo.h"
const int COST_OF_LIVES = 350;
const int COST_OF_UPGRADE = 200;
class UpgradeScreen
{
private:
	sf::Texture goldStar;
	sf::Texture blackStar;
	sf::Texture bgTexture;
	sf::Texture buttonTexture;
	sf::Sprite bg_Sprite;
	sf::Sprite lives_sprite[5];
	sf::Sprite Endurance_sprite[5];
	sf::Sprite buttonSprite[3];
	sf::Font f;
	sf::Text t;
	int mouseX;
	int originalEndurance;
	int originalScore;
	int originalLives;
	int mouseY;
	Sounds* s_Sound = Sounds::getInstance();
	GameStates* g_States = GameStates::getInstance();
	LevelManager* levelManager;
	playerInfo* p;
	bool mouseClicked = false;
	int noOfEnduranceStars;
	int noOfLivesStars;
	int livesSelected;
	int previousLivesSel;
	sf::RenderWindow* m_win;
	Player*m_player;
	void displayLivesAndScore(Vector2f mousePos);
	void displayEnduranceLevel();
	void displayNumberOfLives();
	void LoadAssets();
public:
	UpgradeScreen(sf::RenderWindow*);
	~UpgradeScreen();
	void UpdateStars(Vector2f mousePos);
	void DisplayScreen(Vector2f mousePos);
	void setOriginals() {
		originalEndurance = p->getEnduranceLevel();
		originalScore = p->getScore();
		originalLives = p->getLives();
	}

};

