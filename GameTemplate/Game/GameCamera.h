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
	/// �X�V
	/// </summary>
	void Update();
private:
	float Acos(float angle)  //�O�������̒l����苗���𒴂��Ȃ��悤��
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
	Player * m_player = nullptr;	//�v���C���[�B
	SpringCamera m_characon;
	bool GoalCamera = false;		//�S�[���J�����p�̃t���O
	
};