#pragma once
#include <SFML/Graphics.hpp>

class Particle : public sf::Drawable, public sf::Transformable
{
public:
	Particle(sf::Vector2f pos, sf::RenderWindow* win);
	~Particle();

	void update(float time, bool partALive);
	void setLifeTime();
	float distanceFormStart();
	void resetParticles();
	bool getAlive();
	void setVel();
	float getSpeed();
	sf::Vector2f getPos();
	sf::Vector2f getVel();

	sf::Vector2f Normalise(sf::Vector2f vec);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	sf::Vector2f m_pos;
	sf::Vector2f startPos;
	sf::Vector2f m_vel;
	float m_speed;
	float m_lifeTime;
	bool alive;
	float dissolveRatio;
	bool del;
	int alpha;
	sf::RenderWindow* m_win;
	sf::VertexArray m_vertices;


	
};

//class Particle
//{
//public:
//	Particle(sf::Vector2f position, sf::Vector2f direction, float speed, int type);
//	~Particle();
//
//	void Update(float time);
//	sf::Vector2f GetPosition() { return m_pos; }
//	bool GetAlive() { return m_alive; }
//	float GetTimePercentageLeft() { return (timeToLive - timeAlive / timeToLive) * 100; }
//	float getOpacity() { return opacity; }
//	int GetType() { return type; }
//
//protected:
//	sf::Vector2f m_pos;
//	sf::Vector2f m_direction;
//	float timeAlive;
//	float timeToLive;
//	float m_speed;
//	float opacity;
//	bool m_alive;
//	int type;
//};

