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
	facingRight = true;
	running = false;
	source = 0;
	AnimateFrames();
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
	dynamicBox.SetAsBox((29/ 2.0f) / SCALE, (33 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.1f;
	fixtureDef.userData = "Player";

	fixtureDef.filter.categoryBits = PLAYER;
	fixtureDef.filter.maskBits = PLATFORM | PICKUP | CRATE | HAZARD | EXIT;

	m_body->CreateFixture(&fixtureDef);
}
void Player::loadAssets()
{

	if (!m_textureRI.loadFromFile("../Assets/idleR.png")){
		std::cout << "error with Texture load for player ";
	}
	if (!m_textureLI.loadFromFile("../Assets/idleL.png")){
		std::cout << "error with Texture load for player ";
	}
	if (!m_textureRR.loadFromFile("../Assets/fullrunR.png")){
		std::cout << "error with Texture load for player ";
	}
	if (!m_textureLR.loadFromFile("../Assets/fullrunL.png")){
		std::cout << "error with Texture load for player ";
	}
	m_sprite.setTexture(m_textureRI);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 20, 32));
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
		facingLeft = true;
		facingRight = false;
		running = true;
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x - 0.03f, m_body->GetPosition().y), 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		facingRight = true;
		facingLeft = false;
		running = true;
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + 0.03f, m_body->GetPosition().y), 0);
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Right) || !Keyboard::isKeyPressed(Keyboard::Left))
	{
		running = false;
		m_sprite.setTextureRect(sf::IntRect(0, 0, 20, 32));
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
void Player::AnimateFrames()
{
	//rec[0] = IntRect(0, 0, 24, 32);
	//rec[1] = IntRect(24, 0, 24, 32);
	//rec[2] = IntRect(48, 0, 24, 32);
	rec[0] = IntRect(74, 0, 24, 32);
	rec[1] = IntRect(100, 0, 26, 32);
	//rec[5] = IntRect(129, 0, 26, 32);
	//rec[6] = IntRect(156, 0, 26, 32);
	//rec[7] = IntRect(183, 0, 24, 32);
	rec[2] = IntRect(208, 0, 24, 32);
	//bottom
	rec[3] = IntRect(0, 33, 24, 32);
	////rec[10] = IntRect(24, 32, 24, 32);
	rec[4] = IntRect(49, 33, 24, 32);
	////rec[12] = IntRect(74, 32, 24, 32);
	rec[5] = IntRect(96, 33, 26, 32);
	////rec[14] = IntRect(129, 32, 26, 32);
	rec[6] = IntRect(149, 33, 26, 32);
	rec[7] = IntRect(179, 33, 24, 32);

}
void Player::update()
{
	animationCheck();
	if (running && facingRight)
	{
		
		frameTiming++;
		m_sprite.setTextureRect(rec[source]);
		if (frameTiming == 5)
		{
			source++;

			frameTiming = 0;
		}
		if (source >= 8)
		{
			source = 0;
		}
	}

	if (resetPos)
	{
		m_body->SetLinearVelocity(b2Vec2(0, 0));
		m_body->SetTransform(b2Vec2(startPosition.x / SCALE, startPosition.y / SCALE), 0);
		resetPos = false;
	}
	m_sprite.setPosition(m_body->GetPosition().x * SCALE-26/2, m_body->GetPosition().y*SCALE-26/2);
}
void Player::animationCheck()
{
	if (running)
	{
		if (facingRight)
		{
			m_sprite.setTexture(m_textureRR);
		}
		if (facingLeft)
		{
			m_sprite.setTexture(m_textureLR);
		}
	}
	else
	{
		if (facingRight)
		{
			m_sprite.setTexture(m_textureRI);
		}
		if (facingLeft)
		{
			m_sprite.setTexture(m_textureLI);
		}
	}
	
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