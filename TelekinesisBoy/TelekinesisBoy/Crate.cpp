#include "stdafx.h"
#include "Crate.h"
enum _entityCatergory{
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008
};

Crate::Crate(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win), startPosition(x, y), size(w, h)
{
	createBox2dBody();
	loadAssets();

}


Crate::~Crate()
{
}
void Crate::createBox2dBody()
{
	m_bodyDef.type =b2_kinematicBody;
	m_bodyDef.position.Set((startPosition.x + size.x / 2.0f) / SCALE, (startPosition.y + size.y / 2.f) / SCALE);
	m_bodyDef.userData = this;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Crate";

	//fixtureDef.filter.categoryBits = PLATFORM;
	//fixtureDef.filter.maskBits =  PLAYER;

	m_body->CreateFixture(&fixtureDef);
}

void Crate::loadAssets()
{
	c_Texture.loadFromFile("../Assets/crate.png");
	c_sprite.setTexture(c_Texture);
	c_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	c_sprite.setPosition(startPosition.x, startPosition.y);

}
void Crate::crateMove(){
	c_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x/2.f, m_body->GetPosition().y*SCALE-size.y/2.f);
}
void Crate::Draw()
{
	m_win->draw(c_sprite);
}
