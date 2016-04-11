#pragma once
#include "MovableObject.h"
class Plank :
	public MovableObject
{
public:
	Plank();
	Plank(b2World* world, RenderWindow* win, float x, float y, float w, float h);
	~Plank();
	void createBox2dBody();
	void loadAssets();
};

