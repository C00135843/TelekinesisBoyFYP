#pragma once

enum _gameStates
{
	MENU = 0,
	GAME = 1,
	EXIT = 2,
	OPTIONS = 3,
	END = 4,
	UPGRADE = 5
};

class GameStates
{
private:
	_gameStates currentState;
	GameStates();
	~GameStates();
public:
	static GameStates* getInstance();
	int CurrentState();
	void setState(int);
};

