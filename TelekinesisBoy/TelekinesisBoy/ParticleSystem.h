#pragma once
#include "SFML/Graphics.hpp"
#include "Particle.h"
#include <list>

using namespace std;
class ParticleSystem
{
private:
	ParticleSystem();
	~ParticleSystem();
	std::vector<Particle*> m_particles;

	sf::Vector2f m_emitter;
	sf::Time m_lifetime;
	sf::Vector2f m_gravity;
	float m_fuel;
	
public:

	void removeParticles(std::size_t i);
	static ParticleSystem* GetInstance();
	void addParticle(int fuel, sf::Vector2f pos, sf::RenderWindow * win);
	void update(sf::Time t, bool partAlive);

	void draw(sf::RenderWindow* win);

};
//class ParticleSystem
//{
//public:
//	static ParticleSystem* GetInstance();
//	~ParticleSystem();
//	void Init();
//	void addParticle(sf::Vector2f newPos, int type);
//	void Update(float time);
//	void Draw(sf::RenderWindow &window);
//
//private:
//	ParticleSystem()
//	{
//
//	}
//	list<Particle*> particles;
//
//
//	sf::Texture m_texture;
//	sf::Sprite m_sprite;
//
//	sf::Texture m_SmokeTexture;
//	sf::Sprite m_SmokeSprite;
//
//	static bool instanceFlag;
//	static ParticleSystem* instance;
//
//	sf::Vector2f Normalise(sf::Vector2f vec);
//};
