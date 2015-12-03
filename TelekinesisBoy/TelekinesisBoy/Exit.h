#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>

using namespace sf;
class Exit
{
public:
	Exit(b2World*, RenderWindow*, float, float, float, float);
	~Exit();
	void createBox2dBody();
	void loadAssets();
	void Draw();
private:
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
	const int SCALE = 30.f;
};

