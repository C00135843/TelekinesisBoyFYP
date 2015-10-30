#include "stdafx.h"
#include "Player.h"

enum _entityCatergory{
	PLATFORM = 0x0001,
	PLAYER = 0x0002
};

const float SCALE = 30.f;



Player::Player(b2World* world, RenderWindow* win, float x, float y) : m_world(world), m_win(win){
	startPosition = b2Vec2(x, y);
	createBox2dBody();
	loadAssets();
	grounded = false;

}
void Player::createBox2dBody()
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(startPosition.x / SCALE, startPosition.y / SCALE);
	m_bodyDef.userData = this;
	m_body = m_world->CreateBody(&m_bodyDef);
	dynamicBox.SetAsBox((26 / 2.0f) / SCALE, (26 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1.f;
	fixtureDef.userData = "Player";

	fixtureDef.filter.categoryBits = PLAYER;
	fixtureDef.filter.maskBits = PLATFORM;

	m_body->CreateFixture(&fixtureDef);
}
void Player::loadAssets()
{
	m_texture.loadFromFile("../Assets/player.png");
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
			//grounded = false;
		}
	}

	// helps with gravity
	velChangeX = desiredVelX - velocity.x;

	impulseX = m_body->GetMass() * desiredVelX;
	impulseY = m_body->GetMass() * desiredVelY;

	m_body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), m_body->GetWorldCenter(), true);

}
void Player::update()
{
	m_sprite.setPosition(m_body->GetPosition().x * SCALE-26/2, m_body->GetPosition().y*SCALE-26/2);
}
void Player::ground()
{
	if (grounded == false)
	{
		grounded = true;
	}
	else
		grounded = false;
}