#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
#include <iostream>
#include "Sounds.h"

using namespace sf;

class MovableObject
{
public:
	MovableObject();
	MovableObject(b2World*, RenderWindow*, float, float, float, float);
	~MovableObject();
	virtual void createBox2dBody();
	virtual void  loadAssets();
	void crateMove(Vector2f m, int);
	void Draw();
	int getWeight();
	bool getLifting() { return lifting; }
	void setLifting(bool l) { lifting = l; }

protected:
	Sprite c_sprite;
	Texture c_Texture;
	b2World* m_world;
	RenderWindow* m_win;
	b2BodyDef m_bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* m_body;
	b2FixtureDef fixtureDef;
	b2Vec2 startPosition;
	b2Vec2 size;
	float mouseX;
	float mouseY;
	const int SCALE = 30.f;
	bool lifting = false;
	int m_weight;
	bool playPowerSound = false;
	bool mouseClicked;
};

