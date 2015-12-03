#pragma once
#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
using namespace sf;
class Pickup
{
public:
	Pickup(b2World*, RenderWindow*, float, float);
	~Pickup();
	void createbox2dBody();
	void loadAssets();
	void draw();
	void animation();
	void animationFrames();
	b2Body* getBody(){ return n_body; }
	void setDelete(){ n_delete = true; };
	bool getDelete(){ return n_delete; };


private:
	sf::Texture n_texture;
	sf::Sprite n_sprite;
	b2World* n_world;
	RenderWindow* n_win;
	b2BodyDef n_bodyDef;
	b2CircleShape dynamicBox;
	b2Body* n_body;
	b2FixtureDef fixtureDef;
	b2Vec2 position;
	int source;
	bool next = true;
	sf::IntRect rec[9];
	int frame = 0;
	float frameTiming = 0;
	bool n_delete;
	


};

