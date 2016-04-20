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
//#include "Player.h"
//#include "Platform.h"
//#include "ContactListener.h"
#include "Menu.h"
//#include "Pickup.h"
//#include "Crate.h"
//#include "Hazard.h"
#include "GameStates.h"
//#include "Button.h"
#include "Sounds.h"
//#include "DebugDraw.h"
#include "UpgradeScreen.h"
//#include "Plank.h"
#include "ParticleSystem.h"
#include "LevelManager.h"
#include <vector>

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

void DisplayOptions(RenderWindow* w);
void Hud(RenderWindow* w, Player*p);
bool showTutorial;
bool mouseClick = false;
static const float SCALE = 30.f;
int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	sf::View player_view(FloatRect(0,0,800,600));
	player_view.zoom(1.f);
	window.setFramerateLimit(60);

	//load a font
	sf::Font font;
	Text pauseText;
	Text tutorial1, tutorial2, tutorial3;
	if (!font.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load for writing onthe walls";
	}
	pauseText.setFont(font);
	pauseText.setCharacterSize(80);
	pauseText.setColor(Color::Red);

	tutorial1.setFont(font);
	tutorial1.setColor(Color::Red);
	tutorial1.setCharacterSize(25);
	tutorial2.setFont(font);
	tutorial2.setColor(Color::Red);
	tutorial2.setCharacterSize(25);	
	tutorial3.setFont(font);
	tutorial3.setColor(Color::Red);
	tutorial3.setCharacterSize(25);
	
	//duration bar for the telekinesis power
	sf::Texture barTexture;
	sf::Sprite barSprite;
	barTexture.loadFromFile("../Assets/player.png");
	barSprite.setTexture(barTexture);
	int barWidth = 300;
	int barheight = 20;
	barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));


	//load background
	sf::Texture background;
	sf::Sprite bgsprite;
	sf::Texture backgroundEnd;
	sf::Sprite bgspriteEnd;
	background.loadFromFile("../Assets/menuBackground.png");
	backgroundEnd.loadFromFile("../Assets/gameover.png");
	bgsprite.setTexture(background);
	bgsprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

	LevelManager* levelManager = new LevelManager(&window);
	UpgradeScreen us = UpgradeScreen(&window,levelManager->getPlayer());
	Menu menu(&window);
	ParticleSystem* p_System = ParticleSystem::GetInstance();
	GameStates* g_States = GameStates::getInstance();
	g_States->setState(MENU);
	Sounds* s_Sound = Sounds::getInstance();
	Sounds::getInstance()->playMenuMusic();

	Time pauseTimer;
	Clock pauseClock;
	Clock clock;
	Time elapsed;
	bool partAlive = false;
	bool drawDebug = false;
	bool pause = false;
	bool liftingObject = false;
	bool liftingPlankObject = false;
	Vector2f mousePos;
	showTutorial = false;
	float levelWidth = 1500;


	//int weight = 0;
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
			if (g_States->CurrentState() == GAME) {

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
						partAlive = true;
						mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						p_System->addParticle(3000,mousePos,&window);
							
					}
					break;
				case Event::MouseButtonReleased:
					if (Event.mouseButton.button == sf::Mouse::Left)
					{
						partAlive = false;
					}
					break;
				}
			}

		}		
		if (g_States->CurrentState()== MENU)
		{
						
			window.clear(sf::Color::Black);
			window.draw(bgsprite);
			player_view.setCenter(400, 300);
			window.setView(player_view);
			menu.draw(window);
		}
		if (g_States->CurrentState() == GAME)
		{
									
			window.clear(sf::Color::Color(125,125,125));
			elapsed = clock.getElapsedTime();
			float deltaTime = elapsed.asSeconds();
			clock.restart();
			
			if (levelManager->getPlayer()->getPosition().x >= levelWidth - window.getSize().x / 2)
			{
				player_view.setCenter(1100, 300);
			}
			else if (levelManager->getPlayer()->getPosition().x >= 400)
			{
				player_view.setCenter(levelManager->getPlayer()->getPosition().x, 300);
			}
			else
			{
				player_view.setCenter(400, 300);
				tutorial1.setPosition(200, window.getView().getCenter().y - 100);
				tutorial2.setPosition(500, window.getView().getCenter().y);
				tutorial3.setPosition(700, window.getView().getCenter().y - 250);
			}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			levelManager->Level1Update(pause, mousePos);
			levelManager->Level1Draw(true);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			Hud(&window, levelManager->getPlayer());
	
			if (!pause)
			{
				pauseText.setPosition(window.getView().getCenter().x - 80, window.getView().getCenter().y - 80);
				window.setView(player_view);
			}

			if (levelManager->getPlayer()->getLives() <= 0)
			{
				g_States->setState(END);
				Sounds::getInstance()->stopLevel1Music();
				Sounds::getInstance()->playMenuMusic();
			}
		
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
				pauseTimer = pauseClock.getElapsedTime();
				if (pauseTimer.asSeconds() > .3f)
				{
					if (pauseText.getColor() == Color::Red)
					{
						pauseText.setColor(Color::White);
					}
					else
					{
						pauseText.setColor(Color::Red);
					}
					pauseClock.restart();
				}
				pauseText.setString("PAUSED");
				window.draw(pauseText);
			}


			p_System->update(elapsed, partAlive);
			p_System->draw(&window);
			

			
		}
		if (g_States->CurrentState() == END)
		{
			window.clear(sf::Color::Black);
			bgspriteEnd.setTexture(backgroundEnd);
			bgspriteEnd.setTextureRect(sf::IntRect(0, 0,503,166));
			bgspriteEnd.setPosition(window.getView().getCenter().x -250, window.getView().getCenter().y - 250);
			window.draw(bgspriteEnd);

		}
		if (g_States->CurrentState() == UPGRADE)
		{
			window.clear(sf::Color::Black);
			mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			us.DisplayScreen(mousePos);
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
void Hud(sf::RenderWindow *win,Player * p)
{
	Text textScore;
	Text textPower;
	sf::Font font;

	Text textLives;
	if (!font.loadFromFile("../Font/leadcoat.ttf"))
	{
		std::cout << "error with font load for player hud";
	}
	textScore.setFont(font);
	textScore.setColor(Color::Red);
	textScore.setCharacterSize(25);
	textLives.setFont(font);
	textLives.setColor(Color::Red);
	textLives.setCharacterSize(25);
	textLives.setString("lives: " + std::to_string(p->getLives()));
	textScore.setString("score: " + std::to_string(p->getScore()));
	textLives.setPosition(win->getView().getCenter().x - 390, win->getView().getCenter().y - 290);
	textScore.setPosition(win->getView().getCenter().x + 300, win->getView().getCenter().y - 290);

	win->draw(textLives);
	win->draw(textScore);
	

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
