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
	FLYINGENEMY = 0X1024,
	LINEOFSIGHT = 0x2048
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
	rangeOfTravel = 300;
	wander = true;
	seeking = false;
	restart = false;
	resetPos = false;
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
	m_bodyDef.awake = true;
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
	
	m_sightBody = m_world->CreateBody(&m_bodyDef);
	m_sightBody->SetGravityScale(0);
	m_sightLine.Set(b2Vec2(0, 0), b2Vec2((100 / SCALE) - startPosition.x / SCALE, (460 / SCALE)-(startPosition.y / SCALE)));
	m_sightfixtureDef.shape = &m_sightLine;
	m_sightfixtureDef.isSensor = true;
	m_sightfixtureDef.density = 1.1f;
	m_sightfixtureDef.userData = "lineOfSight";

	m_sightfixtureDef.filter.categoryBits = LINEOFSIGHT;
	m_sightfixtureDef.filter.maskBits = PLATFORM | CRATE | HAZARD | PLAYER | PLANK;
	m_sightBody->CreateFixture(&m_sightfixtureDef);


	
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
	if (t.x >= m_sprite.getPosition().x - 250 && t.x <= m_sprite.getPosition().x +250)
	{
		if (!restart)
		{
			seeking = true;
			wander = false;
		}
	}

}
float birdEnemy::DistanceBetween()
{
	float distance = sqrt(pow(startPosition.x-22 - m_sprite.getPosition().x, 2) + pow(startPosition.y -20- m_sprite.getPosition().y, 2));
	return distance;
}
void birdEnemy::resetLineSight(Player * p)
{
	b2Fixture* f = m_sightBody->GetFixtureList();

	b2Fixture* fixtureToDestroy = f;			
	m_sightBody->DestroyFixture(fixtureToDestroy);

	m_sightLine.Set(
		b2Vec2((getPosition().x+size.x/2)/SCALE - startPosition.x / SCALE, (getPosition().y+size.x/2)/SCALE -startPosition.y/SCALE), 
		b2Vec2((p->getPosition().x+20/2.f) / SCALE - startPosition.x / SCALE, (p->getPosition().y +32/2.f)/ SCALE - startPosition.y / SCALE));
	m_sightfixtureDef.shape = &m_sightLine;
	m_sightfixtureDef.isSensor = true;
	m_sightfixtureDef.density = 1.1f;
	m_sightfixtureDef.userData = "lineOfSight";

	m_sightfixtureDef.filter.categoryBits = LINEOFSIGHT;
	m_sightfixtureDef.filter.maskBits = PLATFORM | CRATE | HAZARD | PLAYER | PLANK;
	m_sightBody->SetAwake(true);
	m_sightBody->CreateFixture(&m_sightfixtureDef);


}
void birdEnemy::update(Player* p)
{
	if (resetPos)
	{
		m_body->SetLinearVelocity(b2Vec2(0, 0));
		m_body->SetTransform(b2Vec2(startPosition.x / SCALE, startPosition.y / SCALE), 0);
		resetPos = false;
	}
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
		restart = false;
	}
	else if (seeking)
	{
		
		if (!restart)
		{
			m_vel = seek(Vector2f(p->getPosition().x, p->getPosition().y));
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
			m_body->SetLinearVelocity(b2Vec2(m_vel.x, m_vel.y));
		}
		else
		{

			float distance = DistanceBetween();
			if (distance <= 6.0f)
			{
				restart = false;
				seeking = false;
				wander = true;
				m_body->SetLinearVelocity(b2Vec2(0, 0));
			}
			else
			{
				m_vel = seek(Vector2f(startPosition.x - size.x / 2, startPosition.y - size.y / 2));
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
				m_body->SetLinearVelocity(b2Vec2(m_vel.x, m_vel.y));
			}
		}
		restart = false;


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

void birdEnemy::setToWander()
{	
	restart = true;
	//seeking = false;
	//wander = true;
}
void birdEnemy::resetPosition() {
	resetPos = true;
	m_body->SetLinearVelocity(b2Vec2(0, 0));
}

