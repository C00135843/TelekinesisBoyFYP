#ifndef Platform_H
#define Platform_H

#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>

using namespace sf;

class Platform{
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	b2World* m_world;
	RenderWindow* m_win;
	b2BodyDef m_bodyDef;
	b2PolygonShape dynamicBox;
	b2Body* m_body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	b2Vec2 size;
	const int SCALE = 30.f;

public:
	Platform(){};
	Platform(b2World*, RenderWindow*, float, float,float,float);
	void createBox2dBody();
	void loadAssets();
	void draw();

};


#endif