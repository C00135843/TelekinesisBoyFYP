#include "stdafx.h"
#include "Door.h"
#include <iostream>

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
Door::Door(b2World* world, RenderWindow* win, float x, float y, float w, float h) : m_world(world), m_win(win), position(x, y), size(w, h)
{
	rotatingDoor = false;
	createBox2dBody();
	loadAssets();
}


Door::~Door()
{
}
void Door::createBox2dBody()
{
	m_bodyDef.type = b2_kinematicBody;
	m_bodyDef.position.Set((position.x + size.x / 2.f) / SCALE, (position.y + size.y / 2.f) / SCALE);
	m_bodyDef.userData = this;
	//m_bodyDef.angle = 0;
	//m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((size.x/2) / SCALE, (size.y/2) / SCALE, b2Vec2(size.x/2/SCALE,size.y/2/SCALE),0);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.restitution = b2MixRestitution(0, 0);
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Door";

	fixtureDef.filter.categoryBits = DOOR;
	fixtureDef.filter.maskBits =  PLAYER | CRATE ;

	m_body->CreateFixture(&fixtureDef);

}
void Door::loadAssets(){
	m_texture.loadFromFile("../Assets/movabledoor.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	m_sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);


}
void Door::Update()
{
	if (rotatingDoor)
	{
		if (currentAngle != desiredAngle)
		{
			currentAngle -= 2.5;
		}
		m_body->SetTransform(m_body->GetPosition(), currentAngle * 3.14159 / 180);
		
	}
	m_sprite.setRotation(m_body->GetAngle() / 3.14159 * 180);
	//m_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
}
void Door::rotateDoor(){
	std::cout << "Door opening " << std::endl;
	
	rotatingDoor = true;
}
void Door::draw(){
	m_win->draw(m_sprite);
}
