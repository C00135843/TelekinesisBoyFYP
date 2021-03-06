#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
#include "SFML/OpenGL.hpp" 
#include <iostream>
#include "Sounds.h"

using namespace sf;

class Enemy
{
public:
	Enemy();
	Enemy(b2World* world, RenderWindow* win, float x, float y, float w, float h);
	~Enemy();
	virtual void createBox2dBody();
	virtual void LoadAssets();
	void draw();
	virtual void update();
	void moveLeftRight();
	virtual void animationFrames();
	virtual void animate(float i);
	bool getAlive();
	Vector2f getPosition() { return m_sprite.getPosition(); }
	b2Body* getBody() { return m_body; }

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
	float m_speed;

};

