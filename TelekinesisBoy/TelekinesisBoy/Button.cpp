#include "stdafx.h"
#include "Button.h"

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
Button::Button(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win), position(x, y), size(w, h)
{
	createBox2dBody();
	loadAssets();
}


Button::~Button()
{
}
void Button::createBox2dBody()
{
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set((position.x + size.x / 2.0f) / SCALE, (position.y + size.y+4) / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.angle = 0;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);

	dynamicBox.SetAsBox((size.x / 2.f) / SCALE, (size.y / 2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Button";


	fixtureDef.filter.categoryBits = BUTTON;
	fixtureDef.filter.maskBits = PLAYER | CRATE | PLATFORM;

	m_body->CreateFixture(&fixtureDef);
}

void Button::loadAssets()
{
	b_Texture.loadFromFile("../Assets/button.png");
	b_sprite.setTexture(b_Texture);
	b_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	b_sprite.setPosition(position.x, position.y);
	//c_sprite.setOrigin(16,16);

}
void Button::Draw()
{
	m_win->draw(b_sprite);
}
