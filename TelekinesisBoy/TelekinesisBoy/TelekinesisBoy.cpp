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
#include "Menu.h"
#include "Pickup.h"
#include "Crate.h"
#include "Hazard.h"
#include "Exit.h"
#include <vector>

enum _gameStates
{
	MENU = 0,
	GAME = 1,
	EXIT = 2,
	OPTIONS = 3,
	END = 4
};

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
static const float SCALE = 30.f;
int main()
{
	std::vector<Pickup*> pickupScheduledForRemoval;
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	sf::View player_view(FloatRect(0,0,800,600));
	player_view.zoom(1.f);

	
	window.setFramerateLimit(60);

	sf::Font font;
	Text textScore;
	Text textLives;
	if (!font.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load for player hud";
	}
	textScore.setFont(font);
	textScore.setColor(Color::Red);
	textScore.setCharacterSize(15);

	textLives.setFont(font);
	textLives.setColor(Color::Red);
	textLives.setCharacterSize(15);
	//load a font
	sf::Texture background;
	sf::Sprite bgsprite;

	background.loadFromFile("../Assets/menuBackground.png");
	bgsprite.setTexture(background);
	bgsprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
	
	bool tb_delete = false;
	//setup the world properties
	int gameState = MENU;
	b2Vec2 gravity(0, 9.81f);
	b2World world(gravity);

	ContactListener contact = ContactListener();
	world.SetContactListener(&contact);
	Platform ground = Platform(&world, &window, 1, 500,800,16);
	std::vector<Crate*>crates;
	int const numOfCrates = 9;
	crates.reserve(numOfCrates);
	float pos = 300;
	for (int i = 0,k=0,j=0; i < numOfCrates; i++){
		Crate* c = new Crate(&world, &window, pos + k * 34, 468 - j * 34, 32, 32);
		crates.push_back(c);
		if (i == 4 )
		{
			k = 1;
			j = 1;
		}
		else if (i == 7)
		{
			k = 2;
			j = 2;
		}
		else
			k++;
	}
	Hazard h = Hazard(&world, &window, 800, 500, 300, 16);
	Exit e = Exit(&world, &window, 0, 453, 61, 47);
	Player p = Player(&world, &window, 100, 1);
	std::vector<Pickup*>neuros;
	Pickup* n = new Pickup(&world, &window, 320, 460);
	Pickup* n1 = new Pickup(&world, &window, 360, 460);
	Pickup* n2 = new Pickup(&world, &window, 400, 460);
	Pickup* n3 = new Pickup(&world, &window, 360, 420);
	neuros.push_back(n);
	neuros.push_back(n1);
	neuros.push_back(n2);
	neuros.push_back(n3);
	//create the size of world

	//create the world

	Menu menu(window.getSize().x, window.getSize().y);

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


			// for menu system
			if (gameState == MENU){
				if ((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::Up))
					menu.MoveUP();
				if ((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::Down))
					menu.MoveDown();
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
				{
					//play game
					if (menu.GetPressedItem() == 0)
					{
						std::cout << "PLAY pressed";
						gameState = GAME;
					}
					// options
					if (menu.GetPressedItem() == 1)
					{
						std::cout << "options pressed";
						//gameState = OPTIONS;
					}
					//exit
					if (menu.GetPressedItem() == 2)
					{
						window.close();
					}
				}
			}
				

		}
		
		
		

		if (gameState == MENU)
		{
			window.clear(sf::Color::Black);
			window.draw(bgsprite);
			menu.draw(window);
		}
		if (gameState == GAME){
			window.clear(sf::Color::White);
			world.Step(1 / 60.f, 8, 3);
			if (p.getPosition().x >= 400)
			{
				player_view.setCenter(p.getPosition().x, 300);
				textLives.setPosition(player_view.getCenter().x - 390, player_view.getCenter().y - 290);
				textScore.setPosition(player_view.getCenter().x, player_view.getCenter().y - 290);
				window.setView(player_view);
			}
			else
			{
				textLives.setPosition(window.getView().getCenter().x - 390, window.getView().getCenter().y - 290);
				textScore.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 290);
			}
			

			ground.draw();
			h.Draw();
			e.Draw();
			// drawing and updating crates
			for (int i = 0; i < crates.size(); i++)
			{
				crates[i]->crateMove();
				crates[i]->Draw();
			}

			p.draw();
			p.movePlayer();
			p.update();
			//how to destroy bodies in box2d
			for (int i = 0; i < neuros.size(); i++)
			{
				tb_delete = neuros[i]->getDelete();
				if (tb_delete)
				{
					pickupScheduledForRemoval.push_back(neuros[i]);
					neuros.erase(neuros.begin() + i);
				}
			}
			if (pickupScheduledForRemoval.size() != 0){
				std::vector<Pickup*>::iterator it = pickupScheduledForRemoval.begin();
				std::vector<Pickup*>::iterator end = pickupScheduledForRemoval.end();
				for (; it != end; ++it){
					Pickup* dyingNeuros = *it;
					world.DestroyBody( dyingNeuros->getBody());
				}
				pickupScheduledForRemoval.clear();
			}
			for (int i = 0; i < neuros.size(); i++){
				neuros[i]->draw();
				neuros[i]->animation();
			}
			if (p.getLives() <= 0)
			{
				gameState = END;
			}
			textLives.setString("lives: " + std::to_string(p.getLives()));
			textScore.setString("score: " + std::to_string(p.getScore()));
			window.draw(textLives);
			window.draw(textScore);

			
		}
		if (gameState == END)
		{
			window.clear(sf::Color::Black);
		}
		
		//prepare frame
		//window.clear(sf::Color::White);


		

		
		//draw frame items
		//window.draw(text);

		//window.draw(circle);


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
