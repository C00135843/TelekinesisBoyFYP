#include "stdafx.h"
#include "Player.h"
#include <iostream>

enum _entityCatergory{
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032,
	BUTTON = 0x0064
};

Player::Player(b2World* world, RenderWindow* win, float x, float y) : m_world(world), m_win(win){
	startPosition = b2Vec2(x, y);
	createBox2dBody();
	loadAssets();
	grounded = false;
	resetPos = false;

}
void Player::createBox2dBody()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(startPosition.x / SCALE, startPosition.y / SCALE);
	m_bodyDef.userData = this;
	m_bodyDef.fixedRotation = true;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((26 / 2.0f) / SCALE, (26 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.f;
	fixtureDef.userData = "Player";

	fixtureDef.filter.categoryBits = PLAYER;
	fixtureDef.filter.maskBits = PLATFORM | PICKUP | CRATE | HAZARD | EXIT;

	m_body->CreateFixture(&fixtureDef);
}
void Player::loadAssets()
{

	if (!m_texture.loadFromFile("../Assets/player.png")){
		std::cout << "error with Texture load for player ";
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(startPosition.x,startPosition.y);
	//m_sprite.setOrigin(Vector2f(startPosition.x - m_texture.getSize().x / 2, startPosition.y - m_texture.getSize().y / 2));
}
void Player::draw()
{
	m_win->draw(m_sprite);
}
void Player::movePlayer()
{
	desiredVelX = 0;
	desiredVelY = 0;
	velocity = m_body->GetLinearVelocity();
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x - 0.03f, m_body->GetPosition().y), 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + 0.03f, m_body->GetPosition().y), 0);
	}
	if ((Keyboard::isKeyPressed(Keyboard::Up)))
	{
		if (grounded){
			m_body->SetLinearVelocity(b2Vec2(0, -6));
			grounded = false;
		}
	}
	// helps with gravity
	m_body->ApplyLinearImpulse(b2Vec2(0, 0), m_body->GetWorldCenter(), true);

}
void Player::update()
{
	if (resetPos)
	{
		m_body->SetLinearVelocity(b2Vec2(0, 0));
		m_body->SetTransform(b2Vec2(startPosition.x / SCALE, startPosition.y / SCALE), 0);
		resetPos = false;
	}
	m_sprite.setPosition(m_body->GetPosition().x * SCALE-26/2, m_body->GetPosition().y*SCALE-26/2);
}
void Player::ground()
{
	grounded = true;

}
void Player::notGrounded()
{
	grounded = false;
}
void Player::resetPosition(){
	resetPos = true;
	m_body->SetLinearVelocity(b2Vec2(0, 0));
}