#include "stdafx.h"
#include "LevelManager.h"


LevelManager::LevelManager(sf::RenderWindow *window): m_win(window)
{
	gravity = new b2Vec2(0, 9.81);
	m_world = new b2World(*gravity);
	contact = new ContactListener(m_world);

	debugDraw = new DebugDraw(m_win);
	m_world->SetDebugDraw(debugDraw);
	debugDraw->SetFlags(b2Draw::e_shapeBit);

	m_world->SetContactListener(contact);
	s_Sound = Sounds::getInstance();
	g_States = GameStates::getInstance();

	p = new Player(m_world, m_win, 100, 460);
	Level1Load();
}


LevelManager::~LevelManager()
{
}

void LevelManager::Level1Load()
{
	weight = 0;
	tb_delete = false;
	//pick ups (blue balls)
	int const numOfCrates = 9;
	crates.reserve(numOfCrates);
	float pos = 330;
	for (int i = 0, k = 0, j = 0; i < numOfCrates; i++) {
		Crate* c = new Crate(m_world, m_win, pos + k * 34, 468 - j * 34, 32, 32);
		crates.push_back(c);
		if (i == 4)
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

	n = new Pickup(m_world, m_win, 320, 460);
	n1 = new Pickup(m_world, m_win, 360, 460);
	n2 = new Pickup(m_world, m_win, 400, 460);
	n3 = new Pickup(m_world, m_win, 360, 420);
	n4 = new Pickup(m_world, m_win, 200, 460);
	n5 = new Pickup(m_world, m_win, 500, 460);
	n6 = new Pickup(m_world, m_win, 700, 420);
	n7 = new Pickup(m_world, m_win, 900, 420);
	n8 = new Pickup(m_world, m_win, 1100, 460);
	n9 = new Pickup(m_world, m_win, 1300, 460);
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


	wallLeft = new Platform(m_world, m_win, -16, 0, 16, 600);
	wallRight = new Platform(m_world, m_win, 1500, 0, 16, 600);
	ground = new Platform(m_world, m_win, 1, 500, 600, 16);
	h = new Hazard(m_world, m_win, 600, 500, 300, 16);
	ground2 = new Platform(m_world, m_win, 900, 500, 600, 16);
	roof = new Platform(m_world, m_win, 900, 250, 800, 16);
	b = new Button(m_world, m_win, 950, 224, 57, 26);
	door = new Door(m_world, m_win, 1100, 150, 16, 234);
	e = new Exit(m_world, m_win, 1440, 453, 61, 47);
	plank = new Plank(m_world, m_win, 200, 200, 128, 32);

	//duration bar for the telekinesis power

	barTexture.loadFromFile("../Assets/player.png");
	barSprite.setTexture(barTexture);
	barWidth = 300;
	barheight = 20;
	barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
	bool liftingObject;
	bool liftingPlankObject;


}

void LevelManager::Level1Update(bool pause,sf::Vector2f mousePos)
{

	if (!pause)
	{
		m_world->Step(1 / 60.f, 8, 3);
		mousePos = m_win->mapPixelToCoords(sf::Mouse::getPosition(*m_win));
		// bar hud telekinesis 
	}


	/////////////////////////////////////////////////////update animate and destroy pickups///////////////////////////////////
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
	if (pickupScheduledForRemoval.size() != 0) {
		std::vector<Pickup*>::iterator it = pickupScheduledForRemoval.begin();
		std::vector<Pickup*>::iterator end = pickupScheduledForRemoval.end();
		for (; it != end; ++it) {
			Pickup* dyingNeuros = *it;
			m_world->DestroyBody(dyingNeuros->getBody());
		}
		pickupScheduledForRemoval.clear();
	}
	for (int i = 0; i < neuros.size(); i++) {
		//neuros[i]->draw();
		if (!pause)
			neuros[i]->animation();
	}

	//////////////////////////////////////////////////update crates ////////////////////////////////////
	for (int i = 0; i < crates.size(); i++)
	{
		liftingObject = crates[i]->getLifting();
		if (liftingObject)
		{
			weight = crates[i]->getWeight();
			//barWidth = 300;
			break;
		}
		else
		{
			liftingObject = false;
			//barWidth = 300;
		}
	}
	liftingPlankObject = plank->getLifting();
	if (liftingPlankObject)
	{
		weight = plank->getWeight();
		//barWidth = 300;
		//break;
	}
	else
	{
		liftingPlankObject = false;
		//barWidth = 300;
	}
	if (liftingObject || liftingPlankObject)
	{
		if (!pause)
		{
			barWidth -= weight;
			if (barWidth <= 0)
			{
				barWidth = 0;
				barClock.restart();

			}
		}
		barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
		barSprite.setPosition(m_win->getView().getCenter().x - 150, m_win->getView().getCenter().y - 200);
		m_win->draw(barSprite);
	}


	if (barWidth == 0 || !liftingObject && !liftingPlankObject)
	{
		Time bTime = barClock.getElapsedTime();
		if (bTime.asSeconds() > 1)
		{
			barWidth = 300;
			barClock.restart();
		}
	}
	

	
	if (!pause)
	{
		door->Update();
		plank->crateMove(mousePos, barWidth);
		p->movePlayer();
		p->update();
	}

	
	for (int i = 0; i < crates.size(); i++)
	{
		if (!pause)
		{
			crates[i]->crateMove(mousePos, barWidth);
		}

	}

}

void LevelManager::Level1Draw(bool drawDebug)
{

	for (int i = 0; i < neuros.size(); i++) {
		neuros[i]->draw();
	}

	ground->draw();
	ground2->draw();
	roof->draw();
	h->Draw();
	e->Draw();
	door->draw();
	b->Draw();

	for (int i = 0; i < crates.size(); i++)
	{
		crates[i]->Draw();
	}
	plank->Draw();
	p->draw();
	if (drawDebug)
		m_world->DrawDebugData();
}

void LevelManager::Level1Del()
{
}

void LevelManager::Level2Load()
{
}

void LevelManager::Level2Update()
{
}

void LevelManager::Level2Draw()
{
}

void LevelManager::Level2Del()
{
}

void LevelManager::Level3Load()
{
}

void LevelManager::Level3Update()
{
}

void LevelManager::Level3Draw()
{
}

void LevelManager::Level3Del()
{
}

Player* LevelManager::getPlayer()
{
	return p;
}
