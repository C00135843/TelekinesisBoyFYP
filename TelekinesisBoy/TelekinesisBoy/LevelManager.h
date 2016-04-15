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

class LevelManager
{
public:
	LevelManager(b2World *world, sf::RenderWindow *window);
	~LevelManager();
	void Level1Load();
	void Level1Update(bool pause);
	void Level1Draw();
	void Level1Del();

	void Level2Load();
	void Level2Update();
	void Level2Draw();
	void Level2Del();

	void Level3Load();
	void Level3Update();
	void Level3Draw();
	void Level3Del();

private:
	b2World* m_world;
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

	Platform* wallLeft;
	Platform* wallRight;
	Platform* ground;
	Hazard* h;
	Platform* ground2;
	Platform* roof;
	Button* b;
	Door* door;
	Exit* e;
	Plank* plank;
	std::vector<Crate*>crates;

	bool tb_delete;

	////////////////////////////////////////bar Hud/////////////////////////
	sf::Texture barTexture;
	sf::Sprite barSprite;
	int barWidth;
	int barheight;

	bool liftingObject = false;
	bool liftingPlankObject = false;


};

