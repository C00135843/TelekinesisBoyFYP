#pragma once
class playerInfo
{
public:
	playerInfo();
	~playerInfo();
	static playerInfo * getInstance();
	void setScore(int s) { score = s; }
	void increaseScore(int is) { score += is; }
	void decreaseLives() { lives--; }
	void setLives(int l) { lives = l; }
	void increaseLives(int l) { lives += l; }
	int getScore() { return score; }
	int getLives() { return lives; }
	void decreaseScore(int ds) { score -= ds; }
	int getEnduranceLevel() { return enduranceLevel; }
	void increaseEnduranceLevel(int el) { enduranceLevel = el; }
private:
	int score;
	int lives;
	int enduranceLevel;
};

