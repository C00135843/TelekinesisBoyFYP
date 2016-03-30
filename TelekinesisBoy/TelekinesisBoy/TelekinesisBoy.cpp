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
#include "GameStates.h"
#include "Button.h"
#include "Door.h"
#include "Sounds.h"
#include "DebugDraw.h"
#include "UpgradeScreen.h"
#include "ParticleSystem.h"
#include <vector>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

void DisplayOptions(RenderWindow* w);
bool showTutorial;
bool mouseClick = false;
static const float SCALE = 30.f;
int main()
{
	std::vector<Pickup*> pickupScheduledForRemoval;
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	sf::View player_view(FloatRect(0,0,800,600));
	player_view.zoom(1.f);
	window.setFramerateLimit(60);
	bool partSystemCreated = false;
	float levelWidth = 1500;
	float mouseX;
	float mouseY;
	Vector2f mousePos;
	showTutorial = false;
	UpgradeScreen us = UpgradeScreen(&window);

	GameStates* g_States = GameStates::getInstance();
	g_States->setState(MENU);
	Sounds* s_Sound = Sounds::getInstance();
	Sounds::getInstance()->playMenuMusic();
	
	sf::Font font;
	Text pauseText;

	Text textScore;
	Text tutorial1, tutorial2, tutorial3;
	Text textLives;
	if (!font.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load for player hud";
	}
	pauseText.setFont(font);
	pauseText.setCharacterSize(80);
	pauseText.setColor(Color::Red);
	textScore.setFont(font);
	textScore.setColor(Color::Red);
	textScore.setCharacterSize(25);
	textLives.setFont(font);
	textLives.setColor(Color::Red);
	textLives.setCharacterSize(25);
	tutorial1.setFont(font);
	tutorial1.setColor(Color::Red);
	tutorial1.setCharacterSize(25);
	tutorial2.setFont(font);
	tutorial2.setColor(Color::Red);
	tutorial2.setCharacterSize(25);	
	tutorial3.setFont(font);
	tutorial3.setColor(Color::Red);
	tutorial3.setCharacterSize(25);
	
	//load a font
	sf::Texture background;
	sf::Sprite bgsprite;
	sf::Texture backgroundEnd;
	sf::Sprite bgspriteEnd;
	
	//duration bar for the telekinesis power
	sf::Texture barTexture;
	sf::Sprite barSprite;
	barTexture.loadFromFile("../Assets/player.png");
	barSprite.setTexture(barTexture);
	int barWidth = 300;
	int barheight = 20;
	barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
	bool liftingObject = false;


	//load background
	background.loadFromFile("../Assets/menuBackground.png");
	backgroundEnd.loadFromFile("../Assets/gameover.png");
	bgsprite.setTexture(background);
	bgsprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

	
	bool tb_delete = false;
	bool drawDebug = false;
	bool pause = false;
	//setup the world properties

	b2Vec2 gravity(0, 9.81f);
	b2World world(gravity);

	DebugDraw debugDraw(&window);
	world.SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);

	//level 1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ContactListener contact = ContactListener(&world);
	world.SetContactListener(&contact);

	Platform wallLeft = Platform(&world, &window, -16, 0, 16, 600);
	Platform wallRight = Platform(&world, &window, 1500, 0, 16, 600);
	Platform ground = Platform(&world, &window, 1, 500,600,16);
	Hazard h = Hazard(&world, &window, 600, 500, 300, 16);
	Platform ground2 = Platform(&world, &window, 900, 500, 600, 16);
	Platform roof = Platform(&world, &window, 900, 250, 800, 16);
	Button b = Button(&world, &window, 950, 224, 57, 26);
	Door door = Door(&world, &window, 1100, 150, 16, 234);
	Exit e = Exit(&world, &window, 1440, 453, 61, 47);
	//Exit e = Exit(&world, &window, 0, 453, 61, 47);
	std::vector<Crate*>crates;
	int const numOfCrates = 9;
	crates.reserve(numOfCrates);
	float pos = 330;
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
	
	
	Player p = Player(&world, &window, 100, 460);
	//Player p = Player(&world, &window, 1200, 500);
	std::vector<Pickup*>neuros;
	Pickup* n = new Pickup(&world, &window, 320, 460);
	Pickup* n1 = new Pickup(&world, &window, 360, 460);
	Pickup* n2 = new Pickup(&world, &window, 400, 460);
	Pickup* n3 = new Pickup(&world, &window, 360, 420);
	Pickup* n4 = new Pickup(&world, &window, 200, 460);
	Pickup* n5 = new Pickup(&world, &window, 500, 460);
	Pickup* n6 = new Pickup(&world, &window, 700, 420);
	Pickup* n7 = new Pickup(&world, &window, 900, 420);
	Pickup* n8 = new Pickup(&world, &window, 1100, 460);
	Pickup* n9 = new Pickup(&world, &window, 1300, 460);
	neuros.push_back(n);
	neuros.push_back(n1);
	neuros.push_back(n2);
	neuros.push_back(n3);
	neuros.push_back(n4);
	neuros.push_back(n5);
	neuros.push_back(n6);
	neuros.push_back(n7);
	neuros.push_back(n8);
	neuros.push_back(n9);
	//level 1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::Clock clock;
	sf::Clock partClock;
	sf::Time t;

	//create the size of world
	int count = 0;
	//create the world
	bool playSound = false;
	Menu menu(window.getSize().x, window.getSize().y);
	int weight = 0;
	ParticleSystem particles(2000);
	bool partAlive = false;

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
			if (g_States->CurrentState() == 0){


				if ((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::Up))
				{
					
					Sounds::getInstance()->playMenuSound();
					menu.MoveUP();
				}
				if ((Event.type == sf::Event::KeyReleased) && (Event.key.code == sf::Keyboard::Down))
				{
					Sounds::getInstance()->playMenuSound();
					menu.MoveDown();
					
				}
					
				if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))
				{
					//play game
					if (menu.GetPressedItem() == 0)
					{
						std::cout << "PLAY pressed";
						g_States->setState(GAME);
						Sounds::getInstance()->stopMenuMusic();
						Sounds::getInstance()->playLevel1Music();
					}
					// options
					if (menu.GetPressedItem() == 1)
					{
						std::cout << "options pressed";
						g_States->setState(OPTIONS);
					}
					//exit
					if (menu.GetPressedItem() == 2)
					{
						window.close();
					}
				}
			}
			// check keypress for debug
			if (g_States->CurrentState() == GAME){

				
				switch (Event.type)
				{
				case Event::KeyReleased:
					if (Event.key.code == sf::Keyboard::F1)
					{
						if (drawDebug)
							drawDebug = false;
						else
							drawDebug = true;
					}
					break;
				case Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::P)
					{
						if (!pause)
							pause = true;
						else
							pause = false;
					}
					break;
				case Event::MouseButtonPressed:
					if (Event.mouseButton.button == sf::Mouse::Left)
					{
						mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						//particles = new ParticleSystem(3000);
						particles.setEmitter(mousePos);
						partAlive = true;
					}
					break;
				case Event::MouseButtonReleased:
					if (Event.mouseButton.button == sf::Mouse::Left)
					{
						//particles.erase(particles.end());
						partAlive = false;
							
					}
					break;
				}				

			}

		}// end of event while	
		
		
		if (g_States->CurrentState()== MENU)
		{
						
			window.clear(sf::Color::Black);
			window.draw(bgsprite);
			menu.draw(window);
		}
		if (g_States->CurrentState() == GAME){									
			window.clear(sf::Color::Color(125,125,125));

			if (!pause)
			{
				world.Step(1 / 60.f, 8, 3);
				mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				
				if (p.getPosition().x >= levelWidth - window.getSize().x / 2)
				{
					player_view.setCenter(1100, 300);
				}
				else if (p.getPosition().x >= 400)
				{
					player_view.setCenter(p.getPosition().x, 300);
				}
				else
				{
					player_view.setCenter(400, 300);
					tutorial1.setPosition(200, window.getView().getCenter().y - 100);
					tutorial2.setPosition(500, window.getView().getCenter().y);
					tutorial3.setPosition(700, window.getView().getCenter().y - 250);
				}
				textLives.setPosition(window.getView().getCenter().x - 390, window.getView().getCenter().y - 290);
				textScore.setPosition(window.getView().getCenter().x - 20, window.getView().getCenter().y - 290);
				pauseText.setPosition(window.getView().getCenter().x - 80, window.getView().getCenter().y - 80);
				window.setView(player_view);
				count++;
				// bar hud telekinesis 
				if (weight > 0)
				{
					barWidth -= weight;
					if (barWidth <= 0)
					{
						barWidth = 0;

					}
					barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
				}
				if (liftingObject)
				{
					
					barSprite.setPosition(window.getView().getCenter().x - 150, window.getView().getCenter().y - 200);
					window.draw(barSprite);
					liftingObject = false;
				}
				else
				{
					if (count > 200)
					{
						barWidth = 300;
						count = 0;
					}

				}
			}

			// drawing and updating crates
			ground.draw();
			ground2.draw();
			roof.draw();
			h.Draw();
			e.Draw();
			
			door.draw();
			b.Draw();
			p.draw();
			if (!pause)
			{
				door.Update();
				p.movePlayer();
				p.update();

			}


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
					world.DestroyBody(dyingNeuros->getBody());
				}
				pickupScheduledForRemoval.clear();
			}
			for (int i = 0; i < neuros.size(); i++){
				neuros[i]->draw();
				if (!pause)
					neuros[i]->animation();
			}

			for (int i = 0; i < crates.size(); i++)
			{
				if (!pause)
					crates[i]->crateMove(mousePos, barWidth);
				crates[i]->Draw();

			}
			for (int i = 0; i < crates.size(); i++)
			{
				weight = crates[i]->getWeight();
				liftingObject = crates[i]->getLifting();
				if (weight != 0)
				{
					break;
				}
			}

			if (p.getLives() <= 0)
			{
				g_States->setState(END);
				Sounds::getInstance()->stopLevel1Music();
				Sounds::getInstance()->playMenuMusic();
			}
			
			textLives.setString("lives: " + std::to_string(p.getLives()));
			textScore.setString("score: " + std::to_string(p.getScore()));
			if (showTutorial)
			{
				tutorial1.setString("USE THE LEFT MOUSE CLICK TO MOVE CRATES");
				tutorial2.setString("USE THE CRATES AS A BRIDGE TO PASS SPIKES");
				tutorial3.setString("PUT CRATE ON BUTTON TO OPEN DOOR");
				window.draw(tutorial1);
				window.draw(tutorial2);
				window.draw(tutorial3);
			}
			// pause
			if (pause)
			{
				t = clock.getElapsedTime();
				if (t.asSeconds() > .3f)
				{
					if (pauseText.getColor() == Color::Red)
					{
						pauseText.setColor(Color::White);
					}
					else
					{
						pauseText.setColor(Color::Red);
					}
					clock.restart();
				}
				pauseText.setString("PAUSED");
				window.draw(pauseText);
			}
			//particle updater

			window.draw(textLives);
			window.draw(textScore);
			if (partAlive)
			{
				particles.setEmitter(mousePos);
				sf::Time elapsed = partClock.restart();
				particles.update(elapsed);
				window.draw(particles);
			}


			if (drawDebug)
				world.DrawDebugData();


			
		}
		if (g_States->CurrentState() == END)
		{
			window.clear(sf::Color::Black);
			bgspriteEnd.setTexture(backgroundEnd);
			bgspriteEnd.setTextureRect(sf::IntRect(0, 0,503,166));
			bgspriteEnd.setPosition(window.getView().getCenter().x -250, window.getView().getCenter().y - 250);
			window.draw(bgspriteEnd);
			textScore.setString("YOUR SCORE IS: " +std::to_string(p.getScore()));
			textScore.setPosition(window.getView().getCenter().x - 100, window.getView().getCenter().y - 25);
			window.draw(textScore);
		}
		if (g_States->CurrentState() == UPGRADE)
		{
			window.clear(sf::Color::Black);
			us.DisplayScreen();
		}
		if (g_States->CurrentState() == OPTIONS)
		{
			window.clear(sf::Color::Black);
			DisplayOptions(&window);
		}


	
		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}

void DisplayOptions(sf::RenderWindow *win)
{

	Vector2f mousePos;
	sf::Text tutorialShow;
	sf::Text playSoundShow;
	sf::Texture SwitchOnTexture;
	sf::Texture SwitchOffTexture;
	sf::Sprite tutorialSwitchSprite;
	sf::Sprite soundSwitchSprite;
	sf::Texture backTexture;
	sf::Sprite backSprite;
	
	///////////////////////////////////////////////////////// load assets ////////////////////////////////////////
	if (!SwitchOnTexture.loadFromFile("../Assets/switchOn.png"))
	{
		std::cout << "cant find switch on texture" << std::endl;
	}
	if (!SwitchOffTexture.loadFromFile("../Assets/switchOff.png"))
	{
		std::cout << "cant find switch off texture" << std::endl;
	}
	if (!backTexture.loadFromFile("../Assets/back.png"))
	{
		std::cout << "cant find back texture" << std::endl;
	}
	backSprite.setTexture(backTexture);
	backSprite.setPosition(win->getView().getCenter().x-400, win->getView().getCenter().y - 300);
	sf::Font f;
	if (!f.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "cant find font for the options" << std::endl;
	}
	

	tutorialShow.setFont(f);
	tutorialShow.setCharacterSize(80);
	tutorialShow.setString("TUTORIAL");
	tutorialShow.setColor(sf::Color::Red);
	tutorialShow.setPosition(win->getView().getCenter().x - 200, win->getView().getCenter().y - 120);
	playSoundShow.setFont(f);
	playSoundShow.setCharacterSize(80);
	playSoundShow.setString("SOUNDS");
	playSoundShow.setColor(sf::Color::Red);
	playSoundShow.setPosition(win->getView().getCenter().x - 200, win->getView().getCenter().y + 50);
	tutorialSwitchSprite.setPosition(win->getView().getCenter().x + 120, win->getView().getCenter().y - 110);
	soundSwitchSprite.setPosition(win->getView().getCenter().x + 120, win->getView().getCenter().y + 60);

	///////////////////////////////////////// show tutorial and switch ///////////////////////////////
	if (showTutorial)
	{
		//switch on
		tutorialSwitchSprite.setTexture(SwitchOnTexture);
		
	}
	else
		tutorialSwitchSprite.setTexture(SwitchOffTexture);

	//////////////////////////////////////// show play sounds and switch //////////////////////////////
	if (Sounds::getInstance()->getSound())
	{
		soundSwitchSprite.setTexture(SwitchOnTexture);
	}
	else
		soundSwitchSprite.setTexture(SwitchOffTexture);

	///////////////////////////////////////////// click on/off switches /////////////////////////////// 
	if (!mouseClick)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mouseClick = true;
			mousePos = win->mapPixelToCoords(sf::Mouse::getPosition(*win));
		}

	}
	else if (!Mouse::isButtonPressed(Mouse::Left))
	{
		mouseClick = false;
	}

	//clicking tutorial on off
	if (mousePos.x >= tutorialSwitchSprite.getPosition().x && mousePos.x <= tutorialSwitchSprite.getPosition().x + tutorialSwitchSprite.getTexture()->getSize().x
		&& mousePos.y >= tutorialSwitchSprite.getPosition().y && mousePos.y <= tutorialSwitchSprite.getPosition().y + tutorialSwitchSprite.getTexture()->getSize().y)
	{
		if (showTutorial)
		{
			showTutorial = false;
		}
		else
			showTutorial = true;
		if (Sounds::getInstance()->getSound())
			Sounds::getInstance()->playMenuSound();

	}
	//clicking sounds on off
	if (mousePos.x >= soundSwitchSprite.getPosition().x && mousePos.x <= soundSwitchSprite.getPosition().x + soundSwitchSprite.getTexture()->getSize().x
		&& mousePos.y >= soundSwitchSprite.getPosition().y && mousePos.y <= soundSwitchSprite.getPosition().y + soundSwitchSprite.getTexture()->getSize().y)
	{
		if (Sounds::getInstance()->getSound())
		{
			Sounds::getInstance()->setSound(false);
		}
		else
			Sounds::getInstance()->setSound(true);
		if (Sounds::getInstance()->getSound())
		{
			Sounds::getInstance()->playMenuSound();
			Sounds::getInstance()->playMenuMusic();

		}
		else
			Sounds::getInstance()->stopMenuMusic();

	}
	// clicking back
	
	if (mousePos != Vector2f(0,0) && mousePos.x >= backSprite.getPosition().x && mousePos.x <= backSprite.getPosition().x + backSprite.getTexture()->getSize().x
		&& mousePos.y >= backSprite.getPosition().y && mousePos.y <= backSprite.getPosition().y + backSprite.getTexture()->getSize().y)
	{

		if (Sounds::getInstance()->getSound())
			Sounds::getInstance()->playMenuSound();
		GameStates::getInstance()->setState(MENU);
	}
	
	win->draw(tutorialShow);
	win->draw(playSoundShow);
	win->draw(tutorialSwitchSprite);
	win->draw(soundSwitchSprite);
	win->draw(backSprite);

}
