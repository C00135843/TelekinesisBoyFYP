#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include <Box2D\Box2D.h>
using namespace sf;


class Player{
	private:
		b2Vec2 velocity;
		sf::Sprite m_sprite;
		sf::Texture m_textureRR;
		sf::Texture m_textureLR;
		sf::Texture m_textureLI;
		sf::Texture m_textureRI;
		b2World* m_world;
		RenderWindow* m_win;
		b2BodyDef m_bodyDef;
		b2PolygonShape dynamicBox;
		b2Body* m_body;
		b2FixtureDef fixtureDef;
		b2Vec2 startPosition;
		b2Draw *b_draw;
		bool grounded;
		float desiredVelX;
		float desiredVelY;
		float velChangeX;
		float velChangeY;
		float impulseX;
		float impulseY;
		int score = 1000;
		int lives = 3;
		bool resetPos;
		const float SCALE = 30.f;
		bool facingRight;
		bool facingLeft;
		bool running;
		sf::IntRect rec[17]; //animate right
		sf::IntRect rec2[17]; //animate left
		int frame = 0;
		float frameTiming = 0;
		void AnimateFrames();
		int source;
		void animationCheck();
		int enduranceLevel;

	public:
		Player(){};
		Player(b2World*, RenderWindow*,float,float);
		void createBox2dBody();
		void loadAssets();
		void update();
		void draw();
		void drawHud();
		void ground();
		void notGrounded();
		void movePlayer();
		void setScore(int s) { score = s; }
		void increaseScore(int is){ score += is; }
		void decreaseLives(){ lives--; }
		void setLives(int l) { lives = l; }
		void increaseLives(int l) { lives += l; }
		int getScore(){ return score; }
		void resetPosition();
		int getLives(){ return lives; }
		b2Body* getBody(){ return m_body; }
		Vector2f getPosition(){ return m_sprite.getPosition(); }
		int getEnduranceLevel() { return enduranceLevel; }
		void increaseEnduranceLevel(int el) { enduranceLevel = el; }
		void decreaseScore(int ds) { score -= ds; }

};
#endif