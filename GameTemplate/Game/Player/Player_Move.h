#pragma once
#include "Player_State.h"
class Player_Move : public Player_State
{
public:
	Player_Move(Player* pla, Player_StateMachine *psm);
	~Player_Move();
	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// ��]
	/// </summary>
	void Turn();
	/// <summary>
	/// �W�����v
	/// </summary>
	void Jump();
	void MoveAnim();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
private:
	float m_moveSpeedWhenStartJump;						//�W�����v�O�̈ړ����x
};

