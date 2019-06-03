#include "stdafx.h"
#include "Player_Move.h"
#include "Player.h"


Player_Move::Player_Move(Player* pla, Player_StateMachine * psm) : Player_State(pla,psm)
{

}


Player_Move::~Player_Move()
{
}

void Player_Move::Move()
{
	auto MOVE_SPEED = 2500.0f;
	static float MOVE_SPEED_JUMP = 1000.0f;

	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	auto lStick_x = g_pad[0].GetLStickXF();
	auto lStick_y = g_pad[0].GetLStickYF();
	//�J�����̑O�������ƉE�������擾
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();

	if (m_player->GetCharaCon().IsJump()) {
		//�W�����v���ł��ɂ������]���ł���悤�ɂ���B
		cameraForward *= lStick_y * MOVE_SPEED_JUMP * m_deltatime;
		cameraRight *= lStick_x * MOVE_SPEED_JUMP * m_deltatime;
	}
	else {
		cameraForward *= lStick_y * MOVE_SPEED * m_deltatime;
		cameraRight *= lStick_x * MOVE_SPEED * m_deltatime;
	}

	//���C�́B
	auto friction = m_moveSpeed;
	if (m_player->GetCharaCon().IsJump()) {
		//�W�����v���̖��C�́B
		friction *= -2.0f;
	}
	else {
		friction *= -5.0f;
	}
	m_moveSpeed.x += friction.x * m_deltatime;
	m_moveSpeed.z += friction.z * m_deltatime;
	//�����x��������B
	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	m_moveSpeed.y += -1800.0f * m_deltatime;
	if (m_player->GetCharaCon().IsJump()) {
		//�ړ����x�ɐ�����������B
		//�W�����v���ɃW�����v�O��葁���Ȃ邱�Ƃ͂Ȃ��B
		auto moveSpeedXZ = CVector3(m_moveSpeed.x, 0.0f, m_moveSpeed.z);

		if (moveSpeedXZ.LengthSq() > m_moveSpeedWhenStartJump * m_moveSpeedWhenStartJump) {
			moveSpeedXZ.Normalize();
			moveSpeedXZ *= m_moveSpeedWhenStartJump;
			m_moveSpeed.x = moveSpeedXZ.x;
			m_moveSpeed.z = moveSpeedXZ.z;

		}
	}
}

void Player_Move::Turn()
{
	//������ς���B
	if (fabsf(m_moveSpeed.x) > 0.1f
		|| fabsf(m_moveSpeed.z) > 0.1f) {
		auto angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		m_rotation.SetRotation(CVector3::AxisY(), angle);
		//����A�j���[�V�����̍Đ����邽�߂ɃX�e�[�g�̕ύX
		if (m_player->GetCharaCon().IsOnGround()) {
			m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_run);
		}
	}
	else {
		//�ҋ@�A�j���[�V�����̍Đ����邽�߂ɃX�e�[�g�̕ύX
		if (m_player->GetCharaCon().IsOnGround()) {
			m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_idle);
		}
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
		}
	}

	if (m_player->GetCharaCon().IsJump())
	{
		m_player->SetAnimation(PlState::EnAnimationClip::enAnimationClip_jump);
	}
}
void Player_Move::Update()
{
	m_moveSpeed = m_player->GetMoveSpeed();
	m_rotation = m_player->GetRotation();
	Move();
	Turn();
	Jump();
	m_player->SetMoveSpeed(m_moveSpeed);
	m_player->SetRotation(m_rotation);
}