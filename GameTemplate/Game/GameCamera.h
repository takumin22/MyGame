#pragma once
#include "Goal.h"
#include "character/SpringCamera.h"
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
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
private:
	float Acos(float angle)  //前方方向の値が一定距離を超えないように
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
	SpringCamera m_characon;
	bool GoalCamera = false;		//ゴールカメラ用のフラグ
	
};