#include "stdafx.h"
#include "Particle.h"
#include <iostream>

Particle::Particle(sf::Vector2f pos,sf::RenderWindow* win): m_pos(pos),m_win(win)
{
	startPos = m_pos;
	alpha = 255;
	del = false;
	alive = true;
	m_vertices = sf::VertexArray(sf::Points,1);
	m_vertices[0].position = m_pos;
	m_vertices[0].color = sf::Color::Red;
	alive = true;
	setVel();
	setLifeTime();
	
}

Particle::~Particle()
{
}

void Particle::update(float time, bool partAlive)
{

	//alive = partAlive;
	m_lifeTime -= time;
	sf::Vector2f gravity(0, 9.81);
	m_vel.x += gravity.x * time; 
	m_vel.y +=  gravity.y * time;

	m_vertices[0].position.x += m_vel.x * time * m_speed;
	m_vertices[0].position.y += m_vel.y * time * m_speed;
	//dissolveRatio -= 2;
	//m_vertices[0].color.a = static_cast<sf::Uint8>(dissolveRatio);

	if (m_lifeTime >= 0)
	{
		alpha = m_lifeTime * 255;
	}
	m_vertices[0].color.a = alpha;

	if (!partAlive)
	{
		alive = false;
	}
	if (m_lifeTime <= 0)
	{
		if (!alive)
		{
			del = true;
		}
		if (!del)
		{
			setLifeTime();
			resetParticles();
		}	

	}

		



}
void Particle::setLifeTime()
{
		float LO = 0.1f;
		float HI = 3.5f;
		m_lifeTime = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

}
float Particle::distanceFormStart()
{
	sf::Vector2f endPos = m_vertices[0].position;
	float distance = sqrt(pow(startPos.x - endPos.x,2) + pow(startPos.y - endPos.y,2));
	return distance;
}

void Particle::resetParticles(){

		startPos = m_win->mapPixelToCoords(sf::Mouse::getPosition(*m_win));
		setVel();
		m_vertices[0].position = startPos;


}
bool Particle::getAlive()
{
	return del;
}

void Particle::setVel()
{

	float angle = (std::rand() % 360) * 3.14f / 180.f;
	// possible change on velocity start
	m_speed = 0.1f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5.0f - 0.1f)));
	m_vel = sf::Vector2f(cos(angle)*m_speed, std::sin(angle)*m_speed);
	//m_vel = Normalise(m_vel);

}

float Particle::getSpeed()
{
	return m_speed;
}

sf::Vector2f Particle::getPos()
{
	return m_pos;
}

sf::Vector2f Particle::getVel()
{
	return m_vel;
}
sf::Vector2f Particle::Normalise(sf::Vector2f vec)
{
	float len = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	return vec / len;
}
void Particle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

		states.transform *= getTransform();
		states.texture = NULL;
		target.draw(m_vertices, states);

}
//Particle::Particle(sf::Vector2f position, sf::Vector2f direction, float speed, int t)
//{
//	m_pos = position;
//	m_direction = direction;
//	m_alive = true;
//	m_speed = speed;
//	timeAlive = 0;
//	timeToLive = ((rand() % 200) / 100) + 0.2;
//	opacity = 255;
//	type = t;
//}
//
//Particle::~Particle()
//{
//}
//
//void Particle::Update(float time)
//{
//	m_pos += m_direction * time * m_speed;
//
//	timeAlive += time;
//
//
//	if (opacity >= 10)
//		opacity -= time * 300;
//	else
//		opacity = 0;
//
//	if (timeAlive > timeToLive)
//	{
//		m_alive = false;
//	}
//
//}