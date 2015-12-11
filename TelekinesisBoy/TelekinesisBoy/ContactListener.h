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

class ContactListener :public b2ContactListener{
private:
	GameStates* g_states = GameStates::getInstance();
	b2World *w;
public:
	ContactListener(b2World* world) : b2ContactListener() {
		w = world;
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
			else
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->ground();
			}
		}

		//PLAYER AND CRATE
		if (fixAType == "Player" && fixBType == "Crate"
			|| fixAType == "Crate" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();

				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();

			}
			else
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				b2Vec2 posPlat = contact->GetFixtureA()->GetBody()->GetPosition();
				b2Vec2 posPlayer = contact->GetFixtureB()->GetBody()->GetPosition();
				if (posPlat.y - (10 / 60.0f) > posPlayer.y + 16 / 30.0f)
					static_cast<Player*>(bodyUserData)->ground();
			}
		}
		// PLAYER AND EXIT COLLISION

		if (fixAType == "Player" && fixBType == "Exit"
			|| fixAType == "Exit" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				g_states->setState(END);
			}
			else
			{
				g_states->setState(END);
			}

		}

		//CRATE AND BUTTON
		if (fixAType == "Crate" && fixBType == "Button"
			|| fixAType == "Button" && fixBType == "Crate"){
				for (b2Body *b = w->GetBodyList(); b != NULL; b = b->GetNext())
				{
					if (b->GetFixtureList()->GetUserData() == "Door")
					{
						static_cast<Door*>(b->GetFixtureList()->GetUserData())->rotateDoor();
					}
				}

		}

		if (fixAType == "Player" && fixBType == "Pickup"
			|| fixAType == "Pickup" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->increaseScore();
				static_cast<Pickup*>(bodyUserData1)->setDelete();
				

			}
			else
			{
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->increaseScore();
				static_cast<Pickup*>(bodyUserData1)->setDelete();
			}
			
		}
		//PLAYER AND HAZARD

		if (fixAType == "Player" && fixBType == "Hazard"
			|| fixAType == "Hazard" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
			}
			else
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->decreaseLives();
				static_cast<Player*>(bodyUserData)->resetPosition();
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
			else
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->notGrounded();

			}
		}

		if (fixAType == "Player" && fixBType == "Crate"
			|| fixAType == "Crate" && fixBType == "Player"){
			if (fixAType == "Player")
			{
				void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->notGrounded();
			}
			else
			{
				void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData)->notGrounded();
			}
		}
	}
};

#endif