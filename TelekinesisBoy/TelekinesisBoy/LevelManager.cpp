#include "stdafx.h"
#include "LevelManager.h"
#include <string>

static bool instanceFlag = false;
static LevelManager* instance = NULL;
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
	pInfo = playerInfo::getInstance();
	//enduranceLevel = 1;
	//lives = 3;
	//score = 0;
	level = 1;	
	Level1Load();
}


LevelManager::~LevelManager()
{
}

LevelManager * LevelManager::getInstance(sf::RenderWindow * window)
{
	if (!instanceFlag)
	{
		instance = new LevelManager(window);
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void LevelManager::Level1Load()
{
	weight = 0;
	tb_delete = false;
	//boundaries
	wallLeft = new Platform(m_world, m_win, -16, 0, 16, 600);
	wallRight = new Platform(m_world, m_win, 1600, 0, 16, 600);
	//roof = new Platform(m_world, m_win, 900, 250, 800, 16);
	///////////////////////map/////////////////////////////////////////////////////

	map = new tmx::TileMap("../Maps/Level1.tmx");
	map->ShowObjects(false);
	map->GetLayer("Background").visible = true;
	map->GetLayer("Platforms").visible = true;
	map->GetObjectGroup("levelObject").visible = false;
	tmx::ObjectGroup t = map->GetObjectGroup("levelObject");
	//String x, y,type,id,width,height;
	int length = t.objects_.size();
	for (int i = 0; i < length; i++)
	{
		std::string type = t.objects_[i].GetPropertyValue("type");
		auto x = atoi(t.objects_[i].GetPropertyValue("x").c_str());
		auto y = atoi(t.objects_[i].GetPropertyValue("y").c_str());
		auto width = atoi(t.objects_[i].GetPropertyValue("width").c_str());
		auto height = atoi(t.objects_[i].GetPropertyValue("height").c_str());
		if (type == "platform")
		{
			Platform* g = new Platform(m_world, m_win, x, y, width, height);
			ground.push_back(g);
		}
		else if (type == "hazard")
		{
			Hazard* h = new Hazard(m_world, m_win, x, y, width, height);
			hazard.push_back(h);
		}
		else if (type == "crate")
		{
			Crate* c = new Crate(m_world, m_win, x, y, width, height);
			crates.push_back(c);
		}
		else if (type == "player")
		{
			p = new Player(m_world, m_win, x, y);
		}
		else if (type == "neuros")
		{
			Pickup* n = new Pickup(m_world, m_win, x, y);
			neuros.push_back(n);
		}
		else if (type == "door")
		{
			door = new Door(m_world, m_win, x, y - height / 2, width, height);
		}
		else if (type == "button")
		{
			b = new Button(m_world, m_win, x, y, width, height);
		}
		else if (type == "exit")
		{
			e = new Exit(m_world, m_win, x, y, width, height);
		}
	}

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
	//liftingPlankObject = plank->getLifting();
	//if (liftingPlankObject)
	//{
	//	weight = plank->getWeight();
	//	//barWidth = 300;
	//	//break;
	//}
	//else
	//{
	//	liftingPlankObject = false;
	//	//barWidth = 300;
	//}
	if (liftingObject || liftingPlankObject)
	{
		if (!pause)
		{
			float x = (static_cast<float>(weight) / pInfo->getEnduranceLevel());
			barWidth -= x;
			if (barWidth <= 0)
			{
				barWidth = 0;
				barClock.restart();

			}
		}
		barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
		barSprite.setPosition(m_win->getView().getCenter().x - 150, m_win->getView().getCenter().y - 200);
		//m_win->draw(barSprite);
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
		//plank->crateMove(mousePos, barWidth);
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
	m_win->draw(*map);
	for (int i = 0; i < neuros.size(); i++) {
		neuros[i]->draw();
	}
	for (int i = 0; i < ground.size(); i++) {
		ground[i]->draw();
	}
	//roof->draw();

	e->Draw();
	door->draw();
	b->Draw();

	for (int i = 0; i < crates.size(); i++)
	{
		crates[i]->Draw();
	}
	//plank->Draw();
	p->draw();


	if (liftingObject || liftingPlankObject)
	{
		m_win->draw(barSprite);
	}

	if (drawDebug)
		m_world->DrawDebugData();
}

void LevelManager::Level1Del()
{
		std::vector<Pickup*>::iterator it = neuros.begin();
		std::vector<Pickup*>::iterator end = neuros.end();
		for (; it != end; ++it) {
			m_world->DestroyBody((*it)->getBody());
		}
		neuros.clear();

		std::vector<Platform*>::iterator it1 = ground.begin();
		std::vector<Platform*>::iterator end1 = ground.end();
		for (; it1 != end1; ++it1) {
			
			m_world->DestroyBody((*it1)->getBody());
		}
		ground.clear();

		std::vector<Crate*>::iterator it2 = crates.begin();
		std::vector<Crate*>::iterator end2 = crates.end();
		for (; it2 != end2; ++it2) {

			m_world->DestroyBody((*it2)->getBody());
		}
		crates.clear();

		std::vector<Plank*>::iterator it3 = planks.begin();
		std::vector<Plank*>::iterator end3 = planks.end();
		for (; it3 != end3; ++it3) {

			m_world->DestroyBody((*it3)->getBody());
		}
		planks.clear();

		std::vector<Hazard*>::iterator it4 = hazard.begin();
		std::vector<Hazard*>::iterator end4 = hazard.end();
		for (; it4 != end4; ++it4) {

			m_world->DestroyBody((*it4)->getBody());
		}
		hazard.clear();

		m_world->DestroyBody(e->getBody());
		m_world->DestroyBody(door->getBody());
		m_world->DestroyBody(b->getBody());
		m_world->DestroyBody(wallRight->getBody());
		m_world->DestroyBody(wallLeft->getBody());
		m_world->DestroyBody(p->getBody());
		//m_world->DestroyBody(flyingEnemy->getBody());
		//m_world->DestroyBody(flyingEnemy->getsBody());
		//m_world->DestroyBody(walkingEnemy->getBody());

}

void LevelManager::Level2Load()
{
	weight = 0;
	tb_delete = false;
	//boundaries
	wallLeft = new Platform(m_world, m_win, -16, 0, 16, 600);
	wallRight = new Platform(m_world, m_win, 3200, 0, 16, 600);
	//roof = new Platform(m_world, m_win, 900, 250, 800, 16);
	///////////////////////map/////////////////////////////////////////////////////

	map = new tmx::TileMap("../Maps/Level2.tmx");
	//map->ShowObjects(true);
	map->GetLayer("Background").visible = true;
	map->GetLayer("Platforms").visible = true;
	map->GetObjectGroup("levelObject").visible = false;
	tmx::ObjectGroup t = map->GetObjectGroup("levelObject");

	int length = t.objects_.size();
	for (int i = 0; i < length; i++)
	{
		std::string type = t.objects_[i].GetPropertyValue("type");
		auto x = atoi(t.objects_[i].GetPropertyValue("x").c_str());
		auto y = atoi(t.objects_[i].GetPropertyValue("y").c_str());
		auto width = atoi(t.objects_[i].GetPropertyValue("width").c_str());
		auto height = atoi(t.objects_[i].GetPropertyValue("height").c_str());
		if (type == "platform")
		{
			Platform* g = new Platform(m_world, m_win, x, y, width, height);
			ground.push_back(g);
		}
		else if (type == "hazard")
		{
			Hazard* h = new Hazard(m_world, m_win, x, y, width, height);
			hazard.push_back(h);
		}
		else if (type == "crate")
		{
			Crate* c = new Crate(m_world, m_win, x, y, width, height);
			crates.push_back(c);
		}
		else if (type == "plank")
		{
			Plank* pl = new Plank(m_world, m_win, x, y, width, height);
			planks.push_back(pl);
		}
		else if (type == "player")
		{
			p = new Player(m_world, m_win, x, y);
		}
		else if (type == "neuros")
		{
			Pickup* n = new Pickup(m_world, m_win, x, y);
			neuros.push_back(n);
		}
		else if (type == "door")
		{
			door = new Door(m_world, m_win, x, y - height / 2, width, height);
		}
		else if (type == "button")
		{
			b = new Button(m_world, m_win, x, y, width, height);
		}
		else if (type == "exit")
		{
			e = new Exit(m_world, m_win, x, y, width, height);
		}
		else if (type == "flyingEnemy")
		{
			flyingEnemy = new birdEnemy(m_world, m_win, x, y, width, height);
		}
		else if (type == "walkingEnemy")
		{
			walkingEnemy = new Enemy(m_world, m_win, x, y, width, height);
		}
	}

	//duration bar for the telekinesis power

	barTexture.loadFromFile("../Assets/player.png");
	barSprite.setTexture(barTexture);
	barWidth = 300;
	barheight = 20;
	barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
	bool liftingObject;
	bool liftingPlankObject;
	
}

void LevelManager::Level2Update(bool pause, sf::Vector2f mousePos)
{

	if (!pause)
	{
		m_world->Step(1 / 60.f, 8, 3);
		mousePos = m_win->mapPixelToCoords(sf::Mouse::getPosition(*m_win));
		p->movePlayer();
		p->update();
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

	for (int i = 0; i < planks.size(); i++)
	{
		liftingPlankObject = planks[i]->getLifting();
		if (liftingPlankObject)
		{
			weight = planks[i]->getWeight();
			//barWidth = 300;
			break;
		}
		else
		{
			liftingPlankObject = false;
			//barWidth = 300;
		}
	}

	if (liftingObject || liftingPlankObject)
	{
		if (!pause)
		{
			float x = (static_cast<float>(weight) / pInfo->getEnduranceLevel());
			barWidth -= x;
			if (barWidth <= 0)
			{
				barWidth = 0;
				barClock.restart();

			}
		}
		barSprite.setTextureRect(IntRect(0, 0, barWidth, barheight));
		barSprite.setPosition(m_win->getView().getCenter().x - 150, m_win->getView().getCenter().y - 200);
		//m_win->draw(barSprite);
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
	door->Update();
	for (int i = 0; i < planks.size(); i++)
	{
		if (!pause)
		{
			planks[i]->crateMove(mousePos, barWidth);
		}

	}
	for (int i = 0; i < crates.size(); i++)
	{
		if (!pause)
		{
			crates[i]->crateMove(mousePos, barWidth);
		}

	}

	flyingEnemy->resetLineSight(p);
	flyingEnemy->update(p);

	walkingEnemy->update();

}

void LevelManager::Level2Draw(bool drawDebug)
{
	m_win->draw(*map);
	
	for (int i = 0; i < ground.size(); i++) {
		ground[i]->draw();
	}
	for (int i = 0; i < neuros.size(); i++) {
		neuros[i]->draw();
	}
	p->draw();

	e->Draw();
	door->draw();
	b->Draw();
	walkingEnemy->draw();
	flyingEnemy->draw();
	if (liftingObject || liftingPlankObject)
	{
		m_win->draw(barSprite);
	}

	for (int i = 0; i < planks.size(); i++)
	{
		planks[i]->Draw();
	}
	for (int i = 0; i < crates.size(); i++)
	{
		crates[i]->Draw();
	}

	if (drawDebug)
		m_world->DrawDebugData();
}

void LevelManager::Level2Del()
{
	std::vector<Pickup*>::iterator it = neuros.begin();
	std::vector<Pickup*>::iterator end = neuros.end();
	for (; it != end; ++it) {
		m_world->DestroyBody((*it)->getBody());
	}
	neuros.clear();

	std::vector<Platform*>::iterator it1 = ground.begin();
	std::vector<Platform*>::iterator end1 = ground.end();
	for (; it1 != end1; ++it1) {

		m_world->DestroyBody((*it1)->getBody());
	}
	ground.clear();

	std::vector<Crate*>::iterator it2 = crates.begin();
	std::vector<Crate*>::iterator end2 = crates.end();
	for (; it2 != end2; ++it2) {

		m_world->DestroyBody((*it2)->getBody());
	}
	crates.clear();

	std::vector<Plank*>::iterator it3 = planks.begin();
	std::vector<Plank*>::iterator end3 = planks.end();
	for (; it3 != end3; ++it3) {

		m_world->DestroyBody((*it3)->getBody());
	}
	planks.clear();

	std::vector<Hazard*>::iterator it4 = hazard.begin();
	std::vector<Hazard*>::iterator end4 = hazard.end();
	for (; it4 != end4; ++it4) {

		m_world->DestroyBody((*it4)->getBody());
	}
	hazard.clear();

	m_world->DestroyBody(e->getBody());
	m_world->DestroyBody(door->getBody());
	m_world->DestroyBody(b->getBody());
	m_world->DestroyBody(wallRight->getBody());
	m_world->DestroyBody(wallLeft->getBody());
	m_world->DestroyBody(p->getBody());
	m_world->DestroyBody(flyingEnemy->getBody());
	m_world->DestroyBody(flyingEnemy->getsBody());
	m_world->DestroyBody(walkingEnemy->getBody());
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


