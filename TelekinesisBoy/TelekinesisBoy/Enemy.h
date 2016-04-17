#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
#include <iostream>
#include "Sounds.h"

using namespace sf;

class Enemy
{
public:
	Enemy();
	Enemy(b2World* world, RenderWindow* win, float x, float y, float w, float h);
	~Enemy();
	void createBox2dBody();
	virtual void LoadAssets();
	void draw();
	virtual void update();
	void moveLeftRight();
	virtual void animationFrames();
	virtual void animate();
	bool getAlive();

protected:
	Sprite m_sprite;
	Texture m_textureR;
	Texture m_textureL;
	sf::IntRect rec[17]; //animate right
	Clock animaterClock;
	Time animaterTime;
	b2World* m_world;
	RenderWindow* m_win;
	b2BodyDef m_bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* m_body;
	b2FixtureDef fixtureDef;
	b2Vec2 startPosition;
	b2Vec2 size;
	float rangeOfTravel;
	bool alive;
	//if facingRight is false it is faceleft
	bool facingRight;
	const float SCALE = 30.f;
	int source1 = 1;
	int source2 = 6;

};

