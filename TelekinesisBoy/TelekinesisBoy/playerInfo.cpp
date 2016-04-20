#include "stdafx.h"
#include "playerInfo.h"

static bool instanceFlag = false;
static playerInfo* instance = NULL;
playerInfo::playerInfo()
{
	score = 100;
	enduranceLevel = 1;
	lives = 3;
}


playerInfo::~playerInfo()
{
}

playerInfo * playerInfo::getInstance()
{
	if (!instanceFlag)
	{
		instance = new playerInfo();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}