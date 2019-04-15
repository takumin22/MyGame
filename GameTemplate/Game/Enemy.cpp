#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "graphics/ShadowMap.h"
#include "Stage.h"

using namespace std;
Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player):
m_position(pos),
m_rotation(rot),
m_player(player)
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/kkk.cmo");
	//�L�����R���ݒ�
	m_charaCon.Init(50.0f, 40.0f, m_position);
}


Enemy::~Enemy()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void Enemy::Move()
{
	idoutime++;
	m_position.x += 5.0f*i;
		//Y�����̈ړ����x�͏d�͉������s���B
		m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);
		m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f*i);
		if (idoutime>= 40) {
			idoutime = 0;
			i *= -1;
		}
}
void Enemy::Search() 
{
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_player->GetPosition() - m_position;
	//�G�l�~�[�܂ł̋��������߂Ă����B
	float toEnemyLen = toEnemyDir.Length();
	if (toEnemyLen < 200.0f) {
		m_estate = State_Tracking;
	}
}
void Enemy::Tracking()
{
	
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayer = m_player->GetPosition() - m_position;
	//�v���C���[�܂ł̋��������߂�
	float len = toPlayer.Length();
	//���K��
	toPlayer.Normalize();
	m_moveSpeed = toPlayer * 200.0f;
	m_moveSpeed.y += -1800.0f * (1.0f / 60.0f);
	if (len > 200.0f) {
		m_estate = State_Move;
	}
	
	//����
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
	//m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy::Damage()
{
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_up = { m_mRot.m[1][0] ,m_mRot.m[1][1] ,m_mRot.m[1][2] };
	CVector3 springForward = CVector3::AxisY();
	m_rotation.Multiply(springForward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_player->GetPosition()  -m_position ;
	//�G�l�~�[�܂ł̋��������߂Ă����B
	float toEnemyLen = toEnemyDir.Length();
	//���K��
	toEnemyDir.Normalize();
	//springForward��toEnemyDir�Ƃ̓��ς��v�Z����B
	float d = toEnemyDir.Dot(m_up);
	//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toEnemyDir�̂Ȃ��p�����߂�B
	float angle = acosf(d);
	 angle = CMath::RadToDeg(angle);


	////�J��������v���C���[�Ɍ������x�N�g�����v�Z����B
	//CVector3 toPlayer = g_camera3D.GetPosition() - m_player->GetPosition();
	//float toEnemyDir = toPlayer.Length();
	////�v���C���[�Ɍ������x�N�g���𐳋K������(�傫��1�ɂ���)�B
	//toPlayer.Normalize();
	////�O�������ƁA�v���C���[�ւ̌����x�N�g���̓��ς��v�Z����B
	//float forward = toPlayer.Dot((m_player->GetUp()));
	////���ς̌��ʂ�cos�ƂɂȂ邽�߁A�Ȃ��p�Ƃ����߂邽�߂�acos�����s����B�B
	//forward = acosf(forward);
	//forward = CMath::RadToDeg(forward);

	//angle = CMath::RadToDeg(angle);
	if (toEnemyLen <= 60.0f &&  angle <= 65.0f) {
		m_estate = State_EDamage;
	}
}
void Enemy::Update()
{

	Damage();
	switch (m_estate)
	{
	case State_Move:
		m_moveSpeed.x = 0.0f;
	    m_moveSpeed.z = 0.0f;
		Move();
	    Search();
		if (m_position.y <= -500.0f) {
			m_estate = State_EDamage;
		
		}
		break;
	case State_Tracking:
		Tracking();
		break;
	case State_EDamage:
		EnemyDeth = true;
		break;
	}
	    m_moveSpeed.y -= 1800.0f /** (1.0f / 60.0f)*/;
		m_charaCon.SetPosition(m_position);
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
		m_model.SetShadowReciever(true);
		//���[���h�s��̍X�V
	    g_shadowMap->RegistShadowCaster(&m_model);
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void Enemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}