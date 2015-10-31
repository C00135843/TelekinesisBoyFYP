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
		float desiredVelX;
		float desiredVelY;
		float velChangeX;
		float velChangeY;
		float impulseX;
		float impulseY;
		int score = 0;
		int lives = 3;


	public:
		Player(){};
		Player(b2World*, RenderWindow*,float,float);
		void createBox2dBody();
		void loadAssets();
		void update();
		void draw();
		void drawHud();
		void ground();
		void movePlayer();
		void increaseScore(){ score += 10; }
		void decreaseLives(){ lives--; }
		int getScore(){ return score; }
		int getLives(){ return lives; }
		b2Body* getBody(){ return m_body; }
		Vector2f getPosition(){ return m_sprite.getPosition(); }

};
#endif