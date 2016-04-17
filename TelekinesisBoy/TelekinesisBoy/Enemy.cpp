#include "stdafx.h"
#include "Enemy.h"

enum _entityCatergory {
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032,
	BUTTON = 0x0064,
	DOOR = 0x0128,
	PLANK = 0x0256,
	WALKINGENEMY = 0x0512,
	FLYINGENEMY = 0X1024
};
Enemy::Enemy()
{
}

Enemy::Enemy(b2World * world, RenderWindow * win, float x, float y, float w, float h) : m_world(world), m_win(win), startPosition(x, y), size(w, h)
{
	alive = true;
	m_speed = 0.08f;
	rangeOfTravel = 300;
	facingRight = true;
	animationFrames();
	createBox2dBody();
	LoadAssets();
}


Enemy::~Enemy()
{
}

void Enemy::createBox2dBody()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(startPosition.x / SCALE, startPosition.y / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((80 / 2.0f) / SCALE, (46 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	//fixtureDef.isSensor = true;
	fixtureDef.density = 1.1f;
	fixtureDef.userData = "walkingEnemy";

	fixtureDef.filter.categoryBits = WALKINGENEMY;
	fixtureDef.filter.maskBits = PLATFORM | CRATE | HAZARD | PLAYER|PLANK;

	m_body->CreateFixture(&fixtureDef);

}

void Enemy::LoadAssets()
{
	if (!m_textureR.loadFromFile("../Assets/robotR.png")) {
		std::cout << "error with Texture load for robot ";
	}
	if (!m_textureL.loadFromFile("../Assets/robotL.png")) {
		std::cout << "error with Texture load for robot ";
	}
	m_sprite.setTexture(m_textureR);
	m_sprite.setTextureRect(rec[0]);
	m_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
}

void Enemy::draw()
{
	m_win->draw(m_sprite);
}

void Enemy::update()
{
	if (m_body->GetPosition().x*SCALE-size.x/2 >= startPosition.x + rangeOfTravel)
	{
		facingRight = false;
	}
	else if (m_body->GetPosition().x*SCALE - size.x / 2 < startPosition.x)
	{
		facingRight = true;
	}
	moveLeftRight();
	animate(.07);
	m_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
}

void Enemy::moveLeftRight()
{
	if (facingRight)
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + m_speed, m_body->GetPosition().y), 0);

	}
	else
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x - m_speed, m_body->GetPosition().y), 0);
	}
	m_body->SetAwake(true);

}

void Enemy::animationFrames()
{
	rec[0] = IntRect(1, 0, 81, 74);
	rec[1] = IntRect(82, 0, 81, 74);
	rec[2] = IntRect(163, 0, 81, 74);
	rec[3] = IntRect(244, 0, 81, 74);
	rec[4] = IntRect(325, 0, 81, 74);
	rec[5] = IntRect(406, 0, 81, 74);
	rec[6] = IntRect(487, 0, 81, 74);
	rec[7] = IntRect(568, 0, 81, 74);
}

void Enemy::animate(float i)
{
	animaterTime = animaterClock.getElapsedTime();
	if (facingRight)
	{
		if (animaterTime.asSeconds() >= i)
		{
			source1++;
			animaterClock.restart();
		}
		if (source1 > 6)
		{
			source1 = 1;
		}
		m_sprite.setTextureRect(rec[source1]);
	}
	else
	{
		if (animaterTime.asSeconds() >= i)
		{
			source2--;
			animaterClock.restart();
		}
		if (source2 < 1)
		{
			source2 = 6;
		}
		m_sprite.setTextureRect(rec[source2]);
	}
	
}

bool Enemy::getAlive()
{
	return alive;
}

