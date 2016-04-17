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

	float angle(sf::Vector2f v);

protected:
	sf::Vector2f seek(sf::Vector2f target);
	void onAlert(sf::Vector2f t);
	bool wander;
	bool seeking;
	float direction;
	sf::Vector2f m_vel;
	float rayAngle = 0;
	float rayLength = 25;
};

