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
#include "Player.h"
#include "Platform.h"
#include "ContactListener.h"



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
	window.setFramerateLimit(60);
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

	b2Vec2 gravity(0, 9.81f);
	b2World world(gravity);

	ContactListener contact = ContactListener();
	world.SetContactListener(&contact);
	Platform ground = Platform(&world, &window, -175, 500,200,16);

	//groundSprite.setRotation(0);

	Player p = Player(&world, &window, 39, 1);
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
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left || Event.key.code == sf::Keyboard::Right))
			{
				p.movePlayer(&Event);
			}

		}
		world.Step(1/60.f, 8, 3);
		//prepare frame
		window.clear(sf::Color::White);
		ground.draw();
		p.draw();
		p.update();

		

		
		//draw frame items
		//window.draw(text);

		//window.draw(circle);


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
