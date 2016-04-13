#include "stdafx.h"
#include "ParticleSystem.h"
#include <iostream>

static bool instanceFlag = false;
static ParticleSystem* instance = NULL;

ParticleSystem::ParticleSystem()
{
	m_gravity = sf::Vector2f(0.f, 9.81f);
	
}


ParticleSystem::~ParticleSystem()
{
}



ParticleSystem* ParticleSystem::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ParticleSystem();
		instanceFlag = true;
		return instance;
	}
	else
		return instance;
}

void ParticleSystem::addParticle(int fuel, sf::Vector2f pos,sf::RenderWindow* win)
{
	for (int i = 0; i < fuel; i++)
	{
		Particle* p = new Particle(pos, win);
		m_particles.push_back(p);
		
	}
}

void ParticleSystem::update(sf::Time t)
{
	float deltaTime = static_cast<float>(t.asSeconds());
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i]->update(deltaTime);

	}
}
void ParticleSystem::draw(sf::RenderWindow * win)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		win->draw(*m_particles[i]);
	}
}

//bool ParticleSystem::instanceFlag = false;
//ParticleSystem* ParticleSystem::instance = NULL;
//
//ParticleSystem* ParticleSystem::GetInstance()
//{
//	if (!instanceFlag)
//	{
//		instance = new ParticleSystem;
//		instanceFlag = true;
//		return instance;
//	}
//	else
//	{
//		return instance;
//	}
//}
//
//
//ParticleSystem::~ParticleSystem()
//{
//}
//
//void ParticleSystem::Init()
//{
//	if (!m_texture.loadFromFile("../Assets/explosion.png"))
//	{
//		std::cout << "no sprite" << std::endl;
//	}
//	m_sprite.setTexture(m_texture);
//
//	if (!m_SmokeTexture.loadFromFile("Smoke.png"))
//	{
//		std::cout << "no sprite" << std::endl;
//	}
//	m_SmokeSprite.setTexture(m_SmokeTexture);
//}
//
//void ParticleSystem::addParticle(sf::Vector2f position, int type)
//{
//
//
//	sf::Vector2f direction = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
//	Particle* p = new Particle(position, Normalise(direction), rand() % 250, type);
//
//	particles.push_back(p);
//
//}
//
//void ParticleSystem::Update(float time)
//{
//
//	list<Particle*>::iterator it = particles.begin();
//	for (it = particles.begin(); it != particles.end();)
//	{
//		(*it)->Update(time);
//		if ((*it)->GetAlive())
//		{
//			++it;
//		}
//		else
//		{
//
//			delete (*it);
//			it = particles.erase(it);
//			//remove from list 
//		}
//	}
//
//
//
//}
//
//void ParticleSystem::Draw(sf::RenderWindow &window)
//{
//	for each (Particle* p in particles)
//	{
//
//		/*int r, g, b;
//		r = rand() % 255;
//		g = rand() % 255;
//		b = rand() % 255;*/
//
//		m_sprite.setColor(sf::Color(255, 255, 255, p->getOpacity()));
//		m_SmokeSprite.setColor(sf::Color(255, 255, 255, p->getOpacity()));
//		if (p->GetType() == 0)
//		{
//			m_sprite.setPosition(p->GetPosition());
//			m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
//			window.draw(m_sprite);
//		}
//		else if (p->GetType() == 1)
//		{
//			m_SmokeSprite.setPosition(p->GetPosition());
//			window.draw(m_SmokeSprite);
//		}
//
//	}
//
//}
//
//sf::Vector2f ParticleSystem::Normalise(sf::Vector2f vec)
//{
//	float len = sqrt((vec.x * vec.x) + (vec.y * vec.y));
//	return vec / len;
//}

