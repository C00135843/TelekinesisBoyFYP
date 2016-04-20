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

	void setOrginalScore(int s) { originalScore = s; }
	void setOriginalEnduranceLevel(int oe) { originalEndurance = oe; }
	void setOriginalLives(int ol) { originalLives = ol; }
	int getOrginalScore() { return originalScore; }
	int getOriginalEnduranceLevel() { return originalEndurance; }
	int getOriginalLives() { return originalLives; }
private:
	int score;
	int lives;
	int enduranceLevel;
	int originalScore;
	int originalLives;
	int originalEndurance;
};

