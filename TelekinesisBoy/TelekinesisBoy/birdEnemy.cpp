#include "stdafx.h"
#include "birdEnemy.h"

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
birdEnemy::birdEnemy()
{
}

birdEnemy::birdEnemy(b2World * world, RenderWindow * win, float x, float y, float w, float h)
{
	m_world = world;
	m_win = win;
	startPosition = b2Vec2(x, y);
	size = b2Vec2(w, h);
	m_speed = 0.03;
	alive = true;
	facingRight = true;
	animationFrames();
	createBox2dBody();
	LoadAssets();
	rangeOfTravel = 500;
	wander = true;
	seeking = false;
}


birdEnemy::~birdEnemy()
{
}

void birdEnemy::createBox2dBody()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(startPosition.x / SCALE, startPosition.y / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);
	m_body->SetGravityScale(0);
	dynamicBox.SetAsBox((size.x / 2.0f) / SCALE, (40 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;
	fixtureDef.density = 1.1f;
	fixtureDef.userData = "flyingEnemy";

	fixtureDef.filter.categoryBits = FLYINGENEMY;
	fixtureDef.filter.maskBits = PLATFORM | CRATE | HAZARD | PLAYER|PLANK;

	m_body->CreateFixture(&fixtureDef);
	
}

void birdEnemy::LoadAssets()
{
	if (!m_textureR.loadFromFile("../Assets/flyingBotR.png"))
	{
		std::cout << "could not find flyingBotR.png" << std::endl;
	}
	if (!m_textureL.loadFromFile("../Assets/flyingBotL.png"))
	{
		std::cout << "could not find flyingBotL.png" << std::endl;
	}
	m_sprite.setTexture(m_textureR);
	m_sprite.setTextureRect(rec[0]);
	m_sprite.setPosition(m_body->GetPosition().x*SCALE - size.x / 2, m_body->GetPosition().y *SCALE - (size.y+5) / 2);
}
void birdEnemy::animationFrames()
{
	rec[0] = IntRect(0, 0, 43, 50);
	rec[1] = IntRect(45, 0, 43, 50);
	rec[2] = IntRect(90, 0, 43, 50);
	rec[3] = IntRect(133, 0, 43, 50);
	rec[4] = IntRect(176, 0, 43, 50);
	rec[5] = IntRect(220, 0, 43, 50);
	rec[6] = IntRect(265, 0, 43, 50);
	rec[7] = IntRect(310, 0, 43, 50);
}
sf::Vector2f birdEnemy::seek(sf::Vector2f target)
{
	float dir_x = target.x - m_sprite.getPosition().x;
	float dir_y = target.y - m_sprite.getPosition().y;
	float length = sqrtf(dir_x*dir_x + dir_y*dir_y);
	dir_x = dir_x / length * 3.5;
	dir_y = dir_y / length * 3.5;
	return sf::Vector2f(dir_x,dir_y);
}
void birdEnemy::onAlert(sf::Vector2f t)
{
	m_vel = seek(Vector2f(t.x, t.y));
	direction = angle(m_vel);

}
void birdEnemy::update(Player* p)
{
	if (wander)
	{
		if (m_body->GetPosition().x*SCALE - size.x / 2 >= startPosition.x + rangeOfTravel)
		{
			facingRight = false;
			m_sprite.setTexture(m_textureL);
		}
		else if (m_body->GetPosition().x*SCALE - size.x / 2 < startPosition.x)
		{
			facingRight = true;
			m_sprite.setTexture(m_textureR);
		}
		moveLeftRight();
		onAlert(p->getPosition());
	}
	else if (seeking)
	{
		m_vel = seek(Vector2f(p->getPosition().x,p->getPosition().y));
		direction = angle(m_vel);
		if (direction > 0 && direction <= 180)
		{
			facingRight = true;
			m_sprite.setTexture(m_textureR);
		}
		else if (direction < 0 && direction >= -180)
		{
			facingRight = false;
			m_sprite.setTexture(m_textureL);
		}
		m_body->SetLinearVelocity(b2Vec2(m_vel.x,m_vel.y));
	}
	
	animate(.1);
	m_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - (size.y + 7) / 2);
}
float birdEnemy::angle(sf::Vector2f v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / 3.14159265359);
	return angle;
}
