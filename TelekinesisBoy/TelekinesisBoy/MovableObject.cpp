#include "stdafx.h"
#include "MovableObject.h"


MovableObject::MovableObject()
{
}

MovableObject::MovableObject(b2World * world, RenderWindow *win, float x, float y, float w, float h):m_world(world), m_win(win), startPosition(x, y), size(w, h)
{
}

MovableObject::~MovableObject()
{
}

void MovableObject::createBox2dBody()
{
}

void MovableObject::loadAssets()
{
}

void MovableObject::crateMove(Vector2f mousePos, int  barTime)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		mouseClicked = true;
		mouseX = mousePos.x;
		mouseY = mousePos.y;
	}
	else
		mouseClicked = false;


	if (mouseClicked && mouseX >= c_sprite.getPosition().x && mouseX <= c_sprite.getPosition().x + c_sprite.getTexture()->getSize().x
		&& mouseY >= c_sprite.getPosition().y && mouseY <= c_sprite.getPosition().y + c_sprite.getTexture()->getSize().y)
	{
		if (barTime > 0)
		{
			lifting = true;
		}

	}
	if (barTime <= 0)
	{
		lifting = false;
	}

	if (!mouseClicked)
	{
		lifting = false;
		if (playPowerSound)
		{
			playPowerSound = false;
			Sounds::getInstance()->stopPowerSound();
		}
	}
	if (mouseClicked && lifting)
	{
		if (!playPowerSound)
		{
			Sounds::getInstance()->playPowerSound();
			playPowerSound = true;
		}
		m_body->SetTransform(b2Vec2((mouseX) / SCALE, (mouseY) / SCALE), 0);
		m_body->SetAwake(true);
		mouseX = 0;
		mouseY = 0;

	}
	else
		if (playPowerSound)
		{
			playPowerSound = false;
			Sounds::getInstance()->stopPowerSound();
		}

	m_body->SetLinearVelocity(b2Vec2(0, 9.81f));
	c_sprite.setPosition(m_body->GetPosition().x *SCALE - size.x / 2, m_body->GetPosition().y*SCALE - size.y / 2);

}

void MovableObject::Draw()
{
	m_win->draw(c_sprite);
}

int MovableObject::getWeight()
{
	if (lifting)
		return m_weight;
	else
		return 0;
}
