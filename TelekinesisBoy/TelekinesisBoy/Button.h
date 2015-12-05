#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>

using namespace sf;
class Button
{
public:
	Button(b2World*, RenderWindow*, float, float, float, float);
	~Button();
	void createBox2dBody();
	void loadAssets();
	void Draw();
private:
	Sprite b_sprite;
	Texture b_Texture;
	b2World* m_world;
	RenderWindow* m_win;
	b2BodyDef m_bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* m_body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	b2Vec2 size;
	const int SCALE = 30.f;
};

