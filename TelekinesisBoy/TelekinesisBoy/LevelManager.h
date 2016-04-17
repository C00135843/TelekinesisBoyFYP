#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <Box2D\Box2D.h>
#include "Platform.h"
#include "Hazard.h"
#include "Button.h"
#include "Door.h"
#include "Exit.h"
#include "Plank.h"
#include "Crate.h"
#include "Pickup.h"
#include <vector>
#include "Player.h"
#include "ContactListener.h"
#include "DebugDraw.h"
#include "GameStates.h"
#include "Sounds.h"
#include "Enemy.h"

class LevelManager
{
public:
	LevelManager(sf::RenderWindow *window);
	~LevelManager();
	void Level1Load();
	void Level1Update(bool pause, sf::Vector2f mousePos);
	void Level1Draw(bool drawDebug);
	void Level1Del();

	void Level2Load();
	void Level2Update(bool pause, sf::Vector2f mousePos);
	void Level2Draw(bool drawDebug);
	void Level2Del();

	void Level3Load();
	void Level3Update();
	void Level3Draw();
	void Level3Del();

	Player * getPlayer();

private:

	b2Vec2* gravity;
	b2World* m_world;
	ContactListener* contact;
	DebugDraw* debugDraw;
	GameStates* g_States;
	Sounds* s_Sound;


	sf::RenderWindow* m_win;
	std::vector<Pickup*> pickupScheduledForRemoval;
	std::vector<Pickup*>neuros;
	Pickup* n;
	Pickup* n1;
	Pickup* n2;
	Pickup* n3;
	Pickup* n4;
	Pickup* n5;
	Pickup* n6;
	Pickup* n7;
	Pickup* n8;
	Pickup* n9;

	Player* p;
	Platform* wallLeft;
	Platform* wallRight;
	Platform* ground;
	Hazard* h;
	Platform* ground2;
	Platform* ground3;
	Platform* ground4;
	Platform* roof;
	Button* b;
	Door* door;
	Exit* e;
	Plank* plank;
	Enemy* walkingEnemy;
	
	std::vector<Crate*>crates;

	bool tb_delete;

	////////////////////////////////////////bar Hud/////////////////////////
	sf::Texture barTexture;
	sf::Sprite barSprite;
	int barWidth;
	int barheight;

	/////////////////////////////////////////lifting items/////////////////////
	bool liftingObject = false;
	bool liftingPlankObject = false;

	int weight;

	Time barTime;
	Clock barClock;

	//Vector2f mousePos;


};

