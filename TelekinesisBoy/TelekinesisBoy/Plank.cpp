#include "stdafx.h"
#include "Plank.h"
enum _entityCatergory {
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032,
	BUTTON = 0x0064,
	PLANK = 0x0128
};

Plank::Plank()
{
}

Plank::Plank(b2World * world, RenderWindow * win, float x, float y, float w, float h): MovableObject(world,win,x,y,w,h)
{
	m_weight = 7.0f;
	createBox2dBody();
	loadAssets();
}

Plank::~Plank()
{
}

void Plank::createBox2dBody()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set((startPosition.x + size.x / 2.f) / SCALE, (startPosition.y + size.y / 2.0f) / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.angle = 0;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);

	dynamicBox.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Plank";

	fixtureDef.filter.categoryBits = PLANK;
	fixtureDef.filter.maskBits = PLAYER | CRATE | PLATFORM | BUTTON | PLANK;

	m_body->CreateFixture(&fixtureDef);
}

void Plank::loadAssets()
{
	c_Texture.loadFromFile("../Assets/crate.png");
	c_Texture.setRepeated(true);
	c_sprite.setTexture(c_Texture);
	c_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	c_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
}
