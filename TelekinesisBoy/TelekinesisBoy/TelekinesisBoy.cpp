// TelekinesisBoy.cpp : Defines the entry point for the console application.
//

//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <Box2D\Box2D.h>
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
void createGround(b2World& world, float x, float y)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(x / 30.0f, y / 30.0f);
	bodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&bodyDef);
	b2PolygonShape Shape;
	Shape.SetAsBox((500.f / 2) / 30.f, (16.f / 2) /30.f);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.3f;
	fixtureDef.userData = "Ground";
	fixtureDef.shape = &Shape;
	Body->CreateFixture(&fixtureDef);


}
static const float SCALE = 30.f;
int main()
{

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");

	//load a font
	/*sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(20, 40);
	text.setCharacterSize(40);

	//create a circle
	sf::CircleShape circle(50);
	circle.setPosition(300, 200);*/

	//setup the world properties
	sf::Texture groundTexture;
	groundTexture.loadFromFile("../Assets/ground.png");

	b2Vec2 gravity(0, 9.8f);
	b2World world(gravity);
	createGround(world, 0.f, 580.f);



	sf::Sprite groundSprite;
	groundSprite.setTexture(groundTexture);
	groundSprite.setPosition(0, 580.f);
	groundSprite.setRotation(0);


	//create the size of world

	//create the world



	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();


		}
		float32 timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 8;
		int32 positionIterations = 3;
		world.Step(timeStep, velocityIterations, positionIterations);
		//prepare frame
		window.clear(sf::Color::White);


		window.draw(groundSprite);

		

		
		//draw frame items
		//window.draw(text);

		//window.draw(circle);


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
