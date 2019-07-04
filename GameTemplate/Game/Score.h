#pragma once
class Score
{
public:
	Score();
	~Score();
	void Relese();
	int GetTotalSocore()
	{
		TotalScore = NScore + TimeScore;
		return TotalScore;
	}
	int  GetTimeScore()
	{
		return TimeScore;
	}
	int GetNScore()
	{
		return NScore;
	}
	void SetNScore(int i) {
		NScore += i;
	}
	void SetTimeScore(int k) {
		TimeScore += k;
	}
private:
	
	int TimeScore = 0;
	int NScore = 0;
	int TotalScore = 0;
};

