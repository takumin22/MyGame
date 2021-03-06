#include "stdafx.h"
#include "Player_Move.h"
#include "Player.h"


Player_Move::Player_Move(Player* pla, Player_StateMachine * psm) : Player_State(pla,psm)
{
	m_jumpse.Init(L"Assets/sound/jump.wav");
	m_jumpse.SetVolume(0.6f);
}


Player_Move::~Player_Move()
{
}

void Player_Move::Move()
{
	auto MOVE_SPEED = 2500.0f;
	static float MOVE_SPEED_JUMP = 1000.0f;

	//左スティックの入力量を受け取る。
	auto lStick_x = g_pad[0].GetLStickXF();
	auto lStick_y = g_pad[0].GetLStickYF();
	//カメラの前方方向と右方向を取得
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();

	if (m_player->GetCharaCon().IsJump()) {
		//ジャンプ中でも緩く方向転換できるようにする。
		cameraForward *= lStick_y * MOVE_SPEED_JUMP * m_deltatime;
		cameraRight *= lStick_x * MOVE_SPEED_JUMP * m_deltatime;
	}
	else {
		cameraForward *= lStick_y * MOVE_SPEED * m_deltatime;
		cameraRight *= lStick_x * MOVE_SPEED * m_deltatime;
	}

	//摩擦力。
	auto friction = m_moveSpeed;
	if (m_player->GetCharaCon().IsJump()) {
		//ジャンプ中の摩擦力。
		friction *= -2.0f;
	}
	else {
		friction *= -5.0f;
	}
	m_moveSpeed.x += friction.x * m_deltatime;
	m_moveSpeed.z += friction.z * m_deltatime;
	//加速度を加える。
	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	m_moveSpeed.y += -1800.0f * m_deltatime;

}

void Player_Move::Turn()
{
	//向きを変える。
	if (fabsf(m_moveSpeed.x) > 0.1f
		|| fabsf(m_moveSpeed.z) > 0.1f) {
		auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3::AxisY(), angle);
	}
}

void Player_Move::Jump()
{
	static float JUMP_SPEED = 700.0f;
	if (m_player->GetCharaCon().IsOnGround()) {
		if (g_pad[0].IsTrigger(enButtonA))
		{
			m_moveSpeedWhenStartJump = m_moveSpeed.Length();
			m_moveSpeed.y = JUMP_SPEED;
			m_jumpse.Play(false);
		}
	}


}
void Player_Move::MoveAnim()
{
	CVector3 move = CVector3::Zero();
	move.x = g_pad[0].GetLStickXF();
	move.z = g_pad[0].GetLStickYF();
	move.y = 0.0f;
	if (m_player->GetCharaCon().IsJump())
	{
		m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_jump);
	}

	//走るアニメーションの再生するためにステートの変更
	if (m_player->GetCharaCon().IsOnGround()) {
		if (move.Length() > 0.001f) {
			m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_run);
		}
		else {
			m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_idle);
		}
	}
}
void Player_Move::Update()
{
	m_moveSpeed = m_player->GetMoveSpeed();
	m_rotation = m_player->GetRotation();
	Move();
	Turn();
	Jump();
	MoveAnim();
	m_player->SetMoveSpeed(m_moveSpeed);
	m_player->SetRotation(m_rotation);
}