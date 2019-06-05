#pragma once
#include "Player_State.h"
class Player_Move : public Player_State
{
public:
	Player_Move(Player* pla, Player_StateMachine *psm);
	~Player_Move();
	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	/// <summary>
	/// 回転
	/// </summary>
	void Turn();
	/// <summary>
	/// ジャンプ
	/// </summary>
	void Jump();
	void MoveAnim();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
private:
	float m_moveSpeedWhenStartJump;						//ジャンプ前の移動速度
};

