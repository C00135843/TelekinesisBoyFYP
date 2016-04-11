#include "stdafx.h"
#include "Crate.h"
enum _entityCatergory{
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032,
	BUTTON = 0x0064,
	PLANK = 0x0128

};

Crate::Crate(b2World* world, RenderWindow* win, float x, float y, float w, float h) : MovableObject(world,win,x,y,w,h)
{
	m_weight = 3.0f;
	createBox2dBody();
	loadAssets();

}
Crate::~Crate()
{
}
 void Crate::createBox2dBody()
{
	m_bodyDef.type =b2_dynamicBody;
	m_bodyDef.position.Set((startPosition.x + size.x / 2.0f) / SCALE, (startPosition.y + size.y / 2.f) / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.angle = 0;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);

	dynamicBox.SetAsBox((size.x/2.f) / SCALE, (size.y/2.f) / SCALE);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 5.f;
	fixtureDef.userData = "Crate";
	

	fixtureDef.filter.categoryBits = CRATE;
	fixtureDef.filter.maskBits =  PLAYER | CRATE | PLATFORM | BUTTON | PLANK;

	m_body->CreateFixture(&fixtureDef);
}

void Crate::loadAssets()
{
	c_Texture.loadFromFile("../Assets/crate.png");
	c_sprite.setTexture(c_Texture);
	c_sprite.setTextureRect(sf::IntRect(0.f, 0.f, size.x, size.y));
	c_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
	//c_sprite.setOrigin(16,16);

}
////void Crate::crateMove(Vector2f mousePos, int barTime){
////
////	if (Mouse::isButtonPressed(Mouse::Left)){
////		mouseClicked = true;
////		mouseX = mousePos.x;
////		mouseY = mousePos.y;
////	}
////	else
////		mouseClicked = false;
////
////
////		if (mouseClicked && mouseX >= c_sprite.getPosition().x && mouseX <= c_sprite.getPosition().x + c_sprite.getTexture()->getSize().x
////			&& mouseY >= c_sprite.getPosition().y && mouseY <= c_sprite.getPosition().y + c_sprite.getTexture()->getSize().y)
////		{
////			if (barTime > 0)
////			{
////				lifting = true;
////			}				
////
////		}	
////		if (barTime <= 0)
////		{
////			lifting = false;
////		}
////	
////	if (!mouseClicked)
////	{
////		lifting = false;
////		if (playPowerSound)
////		{
////			playPowerSound = false;
////			Sounds::getInstance()->stopPowerSound();
////		}
////	}
////	if (mouseClicked && lifting)
////	{
////		if (!playPowerSound)
////		{
////			Sounds::getInstance()->playPowerSound();
////			playPowerSound = true;
////		}
////		m_body->SetTransform(b2Vec2((mouseX) / SCALE, (mouseY) / SCALE), 0);
////		m_body->SetAwake(true);
////		mouseX = 0;
////		mouseY = 0;
////
////	}
////	else
////		if (playPowerSound)
////		{
////			playPowerSound = false;
////			Sounds::getInstance()->stopPowerSound();
////		}
////
////	m_body->SetLinearVelocity(b2Vec2(0, 9.81f));
////	c_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);
////		
////}
//void Crate::Draw()
//{
//	m_win->draw(c_sprite);
//}
//int Crate::getWeight()
//{
//	if (lifting)
//		return weight;
//	else
//		return 0;
//	
//}
