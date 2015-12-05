#include "stdafx.h"
#include "GameStates.h"

static bool instanceFlag = false;
static GameStates* instance = NULL;
GameStates::GameStates()
{
	currentState = _gameStates::MENU;
}


GameStates::~GameStates()
{
}

GameStates* GameStates::getInstance(){
	if (!instanceFlag)
	{
		instance = new GameStates();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
int GameStates::CurrentState(){
	return currentState;
}
void GameStates::setState(int s)
{
	if (s == 0)
	{
		currentState = _gameStates::MENU;
	}
	else if (s == 1)
	{
		currentState = _gameStates::GAME;
	}
	else if (s == 2)
	{
		currentState = _gameStates::EXIT;
	}
	else if (s == 3)
	{
		currentState = _gameStates::OPTIONS;
	}
	else if (s == 4)
	{
		currentState = _gameStates::END;
	}
}
