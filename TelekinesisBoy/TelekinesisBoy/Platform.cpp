#include "stdafx.h"
#include "Platform.h"
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

Platform::Platform(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win){
	position = b2Vec2(x,y);
	size = b2Vec2(w, h);
	createBox2dBody();
	loadAssets();

}

void Platform::createBox2dBody()
{
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set((position.x +size.x/2.f)  / SCALE, (position.y+size.y/2.f) / SCALE);
	m_bodyDef.userData = this;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((size.x / 2.0f) / SCALE, (size.y / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	
	fixtureDef.density = 1.f;
	if (size.x > 16)
	{
		fixtureDef.userData = "Ground";
		fixtureDef.filter.categoryBits = PLATFORM;
		fixtureDef.filter.maskBits = PLAYER | CRATE |LINEOFSIGHT ;
	}
	else
	{
		fixtureDef.userData = "Wall";
		fixtureDef.filter.categoryBits = PLATFORM;
		fixtureDef.filter.maskBits = PLAYER | CRATE| LINEOFSIGHT;
	}

	m_body->CreateFixture(&fixtureDef);
	
}
void Platform::loadAssets(){
	//m_texture.loadFromFile("../Assets/ground.png");
	//m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	m_sprite.setPosition(position.x, position.y);

	
}
void Platform::draw(){
//	m_win->draw(m_sprite);
}
