#pragma once
#include "Goal.h"
class Player;
class Goal;

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
	void Update();
private:
	//enum CameraState
	//{
	//	State_Default,
	//	State_GoalCamera
	//};
	//CameraState m_cmarastate = State_Default;
	float Acos(float angle)
	{
		float a;
		a=min(max(angle,-1.0f), 1.0f);
		return a;
	}
	float Acos2(float angle1)
	{
		float b;
		b = min(max(angle1, -1.0f), 1.0f);
		return b;
	}
	Player * m_player = nullptr;	//プレイヤー。
	bool k = false;
	int kkkkk = 0;
	
};