#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
using namespace sf;
class Player{
	private:
		sf::Vector2f velocity;
		sf::Sprite m_sprite;
		sf::Texture m_texture;
		b2World* m_world;
		sf::Window* win;
		b2Body m_bodyDef;
		b2PolygonShape dynamicBox;
		b2Body* m_body;
		b2FixtureDef fixtureDef;

	public:
		Player(b2World*,float,float);
		void createBox2dBody();
		void loadAssets();
		void update();
		void draw();
		void ground();
		void movePlayer();

};
#endif