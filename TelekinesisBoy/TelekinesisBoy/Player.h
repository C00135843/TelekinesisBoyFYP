#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
using namespace sf;


class Player{
	private:
		b2Vec2 velocity;
		sf::Sprite m_sprite;
		sf::Texture m_texture;
		b2World* m_world;
		RenderWindow* m_win;
		b2BodyDef m_bodyDef;
		b2PolygonShape dynamicBox;
		b2Body* m_body;
		b2FixtureDef fixtureDef;
		b2Vec2 startPosition;
		bool grounded;

	public:
		Player(){};
		Player(b2World*, RenderWindow*,float,float);
		void createBox2dBody();
		void loadAssets();
		void update();
		void draw();
		void ground();
		void movePlayer(sf::Event*);

};
#endif