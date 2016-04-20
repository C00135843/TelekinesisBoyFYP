#include "stdafx.h"
#include "playerInfo.h"

static bool instanceFlag = false;
static playerInfo* instance = NULL;
playerInfo::playerInfo()
{
	score = 0;
	enduranceLevel = 15;
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