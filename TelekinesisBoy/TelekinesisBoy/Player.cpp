#include "stdafx.h"
#include "Player.h"

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

	//fixtureDef.filter.categoryBits = PLAYER;
	//fixtureDef.filter.maskBits = BOUNDARY | PLATFORM | CLOCK | SHROOM | TIMEPICKUP | SPIKE | EXIT;

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
void Player::movePlayer(Event *e)
{
	//velocity = m_body->GetLinearVelocity();
	if ((e->type == sf::Event::KeyPressed) && (e->key.code == sf::Keyboard::Left))
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x - 0.08f, m_body->GetPosition().y), 0);
	}
	if ((e->type == sf::Event::KeyPressed) && (e->key.code == sf::Keyboard::Right))
	{
		m_body->SetTransform(b2Vec2(m_body->GetPosition().x + 0.08f, m_body->GetPosition().y), 0);
	}

}
void Player::update()
{
	if (grounded)
	{
		m_body->GetLinearVelocity();

	}
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