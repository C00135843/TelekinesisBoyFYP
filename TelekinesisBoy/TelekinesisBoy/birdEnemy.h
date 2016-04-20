#pragma once
#include "Enemy.h"
#include "Player.h"
class birdEnemy :
	public Enemy
{
public:
	birdEnemy();
	birdEnemy(b2World* world, RenderWindow* win, float x, float y, float w, float h);
	~birdEnemy();
	void createBox2dBody();
	void LoadAssets();
	void animationFrames();
	void update(Player* p);
	void resetLineSight(Player* p);
	float angle(sf::Vector2f v);
	void setToWander();
	void resetPosition();
	void setToSeek();
	b2Body* getsBody() { return m_sightBody; }

protected:
	sf::Vector2f seek(sf::Vector2f target);
	void onAlert(sf::Vector2f t);
	float DistanceBetween();
	bool wander;
	bool seeking;
	float direction;

	sf::Vector2f m_vel;
	float rayAngle = 0;
	float rayLength = 25;
	b2Body* m_sightBody;
	//b2BodyDef m_sightBodyDef;
	b2EdgeShape m_sightLine;
	b2FixtureDef m_sightfixtureDef;
	bool restart;
	bool resetPos;
};

