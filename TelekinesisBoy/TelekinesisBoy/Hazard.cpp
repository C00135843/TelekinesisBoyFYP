#include "stdafx.h"
#include "Hazard.h"

enum _entityCatergory{
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032
};
Hazard::Hazard(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win), startPosition(x, y), size(w, h)
{
	createBox2dBody();
	loadAssets();
}


Hazard::~Hazard()
{
}
void Hazard::createBox2dBody()
{
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set((startPosition.x + size.x / 2.0f) / SCALE, (startPosition.y + size.y / 2.f) / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.angle = 0;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);

	dynamicBox.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Hazard";


	//fixtureDef.filter.categoryBits = HAZARD;
	//fixtureDef.filter.maskBits = PLAYER ;

	m_body->CreateFixture(&fixtureDef);
}
void Hazard::loadAssets()
{
	c_Texture.loadFromFile("../Assets/hazard.png");
	c_sprite.setTexture(c_Texture);
	c_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	c_sprite.setPosition(startPosition.x, startPosition.y);
	//c_sprite.setOrigin(16,16);

}
void Hazard::Draw()
{
	m_win->draw(c_sprite);
}