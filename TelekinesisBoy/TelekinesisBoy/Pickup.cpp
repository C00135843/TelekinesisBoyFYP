#include "stdafx.h"
#include "Pickup.h"
#include <iostream>

const float SCALE = 30.f;
enum _entityCatergory {
	PLATFORM = 0x0001,
	PLAYER = 0x0002,
	PICKUP = 0x0004,
	CRATE = 0x0008,
	HAZARD = 0x0016,
	EXIT = 0x0032,
	BUTTON = 0x0064,
	DOOR = 0x0128,
	PLANK = 0x0256,
	WALKINGENEMY = 0x0512,
	FLYINGENEMY = 0X1024,
	LINEOFSIGHT = 0x2048
};
enum _animationFrame{
	FIRST = 0 * 42,
	SECOND = 1 * 41,
	THIRD = 2 * 42

};
Pickup::Pickup(b2World* world, RenderWindow* win, float x, float y) : n_world(world), n_win(win){
	position = b2Vec2(x, y);
	createbox2dBody();
	loadAssets();
	source = 0;
	animationFrames();
	n_delete = false;
}

Pickup::~Pickup()
{
}

void Pickup::loadAssets()
{
	if (!n_texture.loadFromFile("../Assets/neuros.png")){
		std::cout << "error with Texture load for player ";
	}
	;
	n_sprite.setTexture(n_texture );
	n_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
	n_sprite.setPosition(position.x, position.y);
	//n_sprite.setOrigin( 20,  20);
}
void Pickup::createbox2dBody(){

	n_bodyDef.type = b2_staticBody;
	n_bodyDef.position.Set((position.x) / SCALE, (position.y) / SCALE);
	n_bodyDef.userData = this;
	n_body = n_world->CreateBody(&n_bodyDef);
	dynamicBox.m_p.Set((40 / 2.0f) / SCALE, (40 / 2.0f) / SCALE);
	dynamicBox.m_radius= 10 /SCALE;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;
	fixtureDef.density = 1.f;
	fixtureDef.userData = "Pickup";

	fixtureDef.filter.categoryBits = PICKUP;
	fixtureDef.filter.maskBits = PLATFORM | PLAYER;

	n_body->CreateFixture(&fixtureDef);

}
void Pickup::draw(){
	n_win->draw(n_sprite);
}
void Pickup::animationFrames(){
	rec[0] = IntRect(FIRST, FIRST, 40, 40);
	rec[1] = IntRect(SECOND,FIRST, 40, 40);
	rec[2] = IntRect(THIRD,FIRST, 40, 40);
	rec[3] = IntRect(FIRST, SECOND, 40, 40);
	rec[4] = IntRect(SECOND, SECOND, 40, 40);
	rec[5] = IntRect(THIRD, SECOND, 40, 40);
	rec[6] = IntRect(FIRST, THIRD, 40, 40);
	rec[7] = IntRect(SECOND, THIRD, 40, 40);
	rec[8] = IntRect(THIRD, THIRD, 40, 40);
}
void Pickup::animation(){

	frameTiming++;

	n_sprite.setTextureRect(rec[source]);
	if (source >= 8)
		next = false;
	if (source <= 0)
		next = true;

	if (frameTiming == 5)
	{
		if (next)
			source++;
		else
			source--;
		frameTiming = 0;
	}





}