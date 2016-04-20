#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h"

#include "Player.h"
#include "Pickup.h"
#include "Platform.h"
#include "GameStates.h"
#include "Crate.h"
#include "Door.h"
#include "Button.h"
#include "Sounds.h"
#include "birdEnemy.h"
#include "playerInfo.h"

class ContactListener :public b2ContactListener{
private:
	GameStates* g_states = GameStates::getInstance();
	b2World *w;
	playerInfo* pi;

public:
	ContactListener(b2World* world) : b2ContactListener() {
		w = world;
		pi = playerInfo::getInstance();
	}
	void BeginContact(b2Contact* contact)
	{
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		if (fixAType == "Player" && fixBType == "Ground"
			|| fixAType == "Ground" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->ground();
			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->ground();
			}
		}
		// FLYING ENEMY AND GROUND
		if (fixAType == "Ground" && fixBType == "lineOfSight"
			|| fixAType == "lineOfSight" && fixBType == "Ground") {
			if (fixAType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
			else if (fixBType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
		}
		// FLYING ENEMY AND CRATE
		if (fixAType == "Crate" && fixBType == "lineOfSight"
			|| fixAType == "lineOfSight" && fixBType == "Crate") {
			if (fixAType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
			else if (fixBType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
		}
		// FLYING ENEMY AND PLANK
		if (fixAType == "Plank" && fixBType == "lineOfSight"
			|| fixAType == "lineOfSight" && fixBType == "Plank") {
			if (fixAType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
			else if (fixBType == "lineOfSight")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				//contact->GetFixtureA()->GetBody()->SetAwake(false);
				static_cast<birdEnemy*>(bodyUserData)->setToWander();
			}
		}

		//PLAYER AND CRATE
		if (fixAType == "Player" && fixBType == "Crate"
			|| fixAType == "Crate" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();

			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();

			}
		}
		//Player and Plank
		if (fixAType == "Player" && fixBType == "Plank"
			|| fixAType == "Plank" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();

				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();

			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();
			}
		}
		// PLAYER AND EXIT COLLISION

		if (fixAType == "Player" && fixBType == "Exit"
			|| fixAType == "Exit" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				g_states->setState(UPGRADE);
				pi->setOrginalScore(pi->getScore());
				pi->setOriginalEnduranceLevel(pi->getEnduranceLevel());
				pi->setOriginalLives(pi->getLives());
				Sounds::getInstance()->stopLevel1Music();
				Sounds::getInstance()->playMenuMusic();
			}
			else if (fixBType == "Player")
			{
				pi->setOrginalScore(pi->getScore());
				pi->setOriginalEnduranceLevel(pi->getEnduranceLevel());
				pi->setOriginalLives(pi->getLives());
				Sounds::getInstance()->stopLevel1Music();
				Sounds::getInstance()->playMenuMusic();
				g_states->setState(UPGRADE);
			}

		}
		//PLAYER AND FLYINGENEMY
		if (fixAType == "Player" && fixBType == "flyingEnemy"
			|| fixAType == "flyingEnemy" && fixBType == "Player") {
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				pi->decreaseLives();
				//static_cast<Player*>(bodyUserData)->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
				static_cast<birdEnemy*>(bodyUserData1)->resetPosition();
				Sounds::getInstance()->playDeathSound();
				//static_cast<birdEnemy*>(bodyUserData1)->setDelete();
			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				//static_cast<Player*>(bodyUserData1)->decreaseLives();
				pi->decreaseLives();
				static_cast<Player*>(bodyUserData1)->resetPosition();
				static_cast<birdEnemy*>(bodyUserData)->resetPosition();
				Sounds::getInstance()->playDeathSound();
			}

		}

		if (fixAType == "Player" && fixBType == "walkingEnemy"
			|| fixAType == "walkingEnemy" && fixBType == "Player") {
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				//static_cast<Player*>(bodyUserData)->decreaseLives();
				pi->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
				Sounds::getInstance()->playDeathSound();
				//static_cast<birdEnemy*>(bodyUserData1)->setDelete();
			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				//static_cast<Player*>(bodyUserData1)->decreaseLives();
				pi->decreaseLives();
				static_cast<Player*>(bodyUserData1)->resetPosition();
				Sounds::getInstance()->playDeathSound();
			}

		}

		//CRATE AND BUTTON
		if (fixAType == "Crate" && fixBType == "Button"
			|| fixAType == "Button" && fixBType == "Crate"){
				for (b2Body *b = w->GetBodyList(); b != NULL; b = b->GetNext())
				{
					if (b->GetFixtureList()->GetUserData() == "Door")
					{
						static_cast<Door*>(b->GetUserData())->rotateDoor();
					}
				}

		}

		if (fixAType == "Player" && fixBType == "Pickup"
			|| fixAType == "Pickup" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				pi->increaseScore(25);
				static_cast<Pickup*>(bodyUserData1)->setDelete();
				Sounds::getInstance()->playPickupSound();
				

			}
			else if (fixBType == "Player")
			{
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				pi->increaseScore(25);
				static_cast<Pickup*>(bodyUserData1)->setDelete();
				Sounds::getInstance()->playPickupSound();
			}
			
		}
		//PLAYER AND HAZARD

		if (fixAType == "Player" && fixBType == "Hazard"
			|| fixAType == "Hazard" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				//static_cast<Player*>(bodyUserData)->decreaseLives();
				pi->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
				Sounds::getInstance()->playDeathSound();
			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				//static_cast<Player*>(bodyUserData)->decreaseLives();
				pi->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
				Sounds::getInstance()->playDeathSound();
			}
		}


	}

	void EndContact(b2Contact* contact)
	{
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		if (fixAType == "Player" && fixBType == "Ground"
			|| fixAType == "Ground" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->notGrounded();

			}
			else if (fixBType == "Player")
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->notGrounded();

			}
		}


		if (fixAType == "Player" && fixBType == "Crate"
			|| fixAType == "Crate" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureB()->GetBody()->GetPosition();
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				if (posPlat.y + (10 / 60.0f) > posPlayer.y - 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->notGrounded();
				else
					static_cast<Player*>(bodyUserData)->ground();
			}
			else if (fixBType == "Player")
			{
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				if (posPlat.y + (10 / 60.0f) > posPlayer.y - 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->notGrounded();
				else
					static_cast<Player*>(bodyUserData)->ground();
			}
		}
		if (fixAType == "Player" && fixBType == "Plank"
			|| fixAType == "Plank" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				b2Vec2 posPlayer = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlat= contact->GetFixtureB()->GetBody()->GetPosition();
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				if (posPlat.y + (10 / 60.0f) > posPlayer.y - 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->notGrounded();
				else
					static_cast<Player*>(bodyUserData)->ground();
			}
			else if (fixBType == "Player")
			{
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				if (posPlat.y + (10 / 60.0f) > posPlayer.y - 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->notGrounded();
				else
					static_cast<Player*>(bodyUserData)->ground();
			}
		}

		//if (fixAType == "Ground" && fixBType == "lineOfSight"
		//	|| fixAType == "lineOfSight" && fixBType == "Ground") {
		//	if (fixAType == "lineOfSight")
		//	{
		//		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		//		//contact->GetFixtureA()->GetBody()->SetAwake(false);
		//		static_cast<birdEnemy*>(bodyUserData)->setToSeek();
		//	}
		//	else if (fixBType == "lineOfSight")
		//	{
		//		void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		//		//contact->GetFixtureA()->GetBody()->SetAwake(false);
		//		static_cast<birdEnemy*>(bodyUserData)->setToSeek();
		//	}
		//}
	}
};

#endif