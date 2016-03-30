#pragma once
#include "SFML/Graphics.hpp"
#include <list>

namespace Shape{ enum { CIRCLE, SWUARE }; }

struct Particle
{
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Color color;
};

typedef std::list<Particle*>::iterator ParticleIter;

class ParticleSystem
{
public:
	ParticleSystem(int width, int height);
	~ParticleSystem();

	void fuel(int particles); 
	void update();
	void remove();
	void render();

	void setPosition(float x, float y);
	void setGravity(float x, float y);
	

private:


};

