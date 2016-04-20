#pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "STP\TMXLoader.hpp"
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
#include "birdEnemy.h"
#include <string>


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
	float getLevel() { return level; }

private:

	b2Vec2* gravity;
	b2World* m_world;
	ContactListener* contact;
	DebugDraw* debugDraw;
	GameStates* g_States;
	Sounds* s_Sound;

	tmx::TileMap* map;
	sf::RenderWindow* m_win;
	std::vector<Pickup*> pickupScheduledForRemoval;
	std::vector<Pickup*>neuros;
	std::vector<Crate*>crates;
	std::vector<Plank*>planks;
	birdEnemy* flyingEnemy;
	Enemy* walkingEnemy;
	Player* p;
	Platform* wallLeft;
	Platform* wallRight;
	std::vector<Platform*> ground;
	std::vector<Hazard*> hazard;

	Platform* roof;
	Button* b;
	Door* door;
	Exit* e;
	//Plank* plank;

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
	int level;
	//Vector2f mousePos;


};

