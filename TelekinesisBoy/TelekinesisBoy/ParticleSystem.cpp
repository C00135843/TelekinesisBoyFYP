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



void ParticleSystem::removeParticles(std::size_t i)
{
	m_particles.erase(m_particles.begin()+i);
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

void ParticleSystem::update(sf::Time t, bool partAlive)
{
	float deltaTime = static_cast<float>(t.asSeconds());
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i]->update(deltaTime, partAlive);
		if (m_particles[i]->getAlive())
		{
			removeParticles(i);
		}
	}
}
void ParticleSystem::draw(sf::RenderWindow * win)
{
	for (int i = 0; i < m_particles.size(); i++)
	{
		win->draw(*m_particles[i]);
	}
	//std::cout <<  m_particles.size() << std::endl;
}

