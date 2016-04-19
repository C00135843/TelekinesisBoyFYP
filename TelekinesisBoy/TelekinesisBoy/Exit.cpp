#include "stdafx.h"
#include "Exit.h"

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
Exit::Exit(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win), startPosition(x, y), size(w, h)
{
	createBox2dBody();
	loadAssets();
}


Exit::~Exit()
{
}
void Exit::createBox2dBody()
{
	m_bodyDef.type =b2_staticBody;
	m_bodyDef.position.Set((startPosition.x + size.x / 2.0f) / SCALE, (startPosition.y + size.y / 2.f) / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.angle = 0;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Exit";


	fixtureDef.filter.categoryBits = EXIT;
	fixtureDef.filter.maskBits = PLAYER ;

	m_body->CreateFixture(&fixtureDef);
}
void Exit::loadAssets()
{
	c_Texture.loadFromFile("../Assets/door.png");
	c_sprite.setTexture(c_Texture);
	c_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	c_sprite.setPosition(startPosition.x, startPosition.y);
	//c_sprite.setOrigin(16,16);

}
void Exit::Draw()
{
	m_win->draw(c_sprite);
}