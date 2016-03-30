#pragma once
#include "SFML/Graphics.hpp"
#include <list>


struct Particle
{
	sf::Vector2f velocity;
	sf::Time lifetime;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(3)),
		m_emitter(0, 0)
	{
	}
	void setEmitter(sf::Vector2f position);

	void update(sf::Time elapsed);
private:
	void resetParticle(std::size_t index);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

};

