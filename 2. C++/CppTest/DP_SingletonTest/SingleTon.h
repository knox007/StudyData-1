#pragma once

#include<iostream>

using namespace std;

class ScoreManager
{
	int score;
public:
	ScoreManager() { score = 0; }
	~ScoreManager() {}
	void AddScore(int val) { score += val; }
	void ShowData() { cout << score << endl; }
};

// answer is as follows....


























/*
class ScoreManager
{
private:
	ScoreManager() { score = 0; }
	static ScoreManager* inst;

	int score;

public:
	static ScoreManager* getInstance()
	{
		if (inst == nullptr)
			inst = new ScoreManager();

		return inst;
	}

	static void Destroy()
	{
		if (inst)
		{
			delete inst;
			inst = NULL;
		}
	}

	void AddScore(int val)	{ score += val;	}

	void ShowData()	{ cout << score << endl; }
};

//	Initialize in .cpp
*/