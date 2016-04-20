#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
#include <math.h>

using namespace sf;
class Door
{
private:
	Sprite m_sprite;
	Texture m_texture;
	b2World* m_world;
	RenderWindow* m_win;
	b2BodyDef m_bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* m_body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	b2Vec2 size;
	float desiredAngle = -90;
	float currentAngle = 0;
	const int SCALE = 30.f;
	bool rotatingDoor = false;
	
public:
	Door(b2World*, RenderWindow*, float, float, float, float);
	~Door();
	void createBox2dBody();
	void loadAssets();
	void draw();
	void rotateDoor();
	void Update();
	b2Body* getBody() { return m_body; }
};

