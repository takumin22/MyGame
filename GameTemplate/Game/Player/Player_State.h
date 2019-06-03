#pragma once
class Player;
class Player_StateMachine;
class Player_State
{
public:
	Player_State(Player* player, Player_StateMachine *psm);
	~Player_State();

	virtual void Update() = 0;
protected:
	Player_StateMachine * m_plstma = nullptr;
	Player * m_player = nullptr;
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();
	float m_deltatime = 1.0f / 30.0f;                   //1フレームの経過時間

};

