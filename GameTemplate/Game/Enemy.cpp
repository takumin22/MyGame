#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "graphics/ShadowMap.h"

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
	m_position.y = 100.0f;
}


Enemy::~Enemy()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void Enemy::RigthMove()
{
	
	m_position.x += -5.0f;
		//Y�����̈ړ����x�͏d�͉������s���B
		m_moveSpeed.y -= 1700.0f * (1.0f / 60.0f);
		m_rotation.SetRotationDeg(CVector3::AxisY(), -90.0f);
		if (m_position.x <= -162.0f) {
			m_estate = State_LeftMove;
		}
		Search();
	
}
void Enemy::LeftMove()
{
	m_position.x += 5.0f;
    //Y�����̈ړ����x�͏d�͉������s���B
	m_moveSpeed.y -= 1700.0f * (1.0f / 60.0f);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f);
	if (m_position.x >= 162.0f) {
		m_estate = State_RigthMove;
	}
	Search();

}
void Enemy::Search() 
{
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_position - m_player->GetPosition();
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
	m_moveSpeed.y += -20.0f * (1.0f / 60.0f);
	if (len > 200.0f) {;
		m_estate = State_LeftMove;
	}
	Damage();
	//����
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy::Damage()
{
	CVector3 springForward = CVector3::AxisY();
	m_rotation.Multiply(springForward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_position - m_player->GetPosition()  ;
	//�G�l�~�[�܂ł̋��������߂Ă����B
	float toEnemyLen = toEnemyDir.Length();
	//���K��
	toEnemyDir.Normalize();
	//springForward��toEnemyDir�Ƃ̓��ς��v�Z����B
	float d = springForward.Dot(toEnemyDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAspringForward��toEnemyDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	//angle = CMath::RadToDeg(angle);
	if ( toEnemyLen <= 700.0f && fabsf(angle) < CMath::DegToRad(45.0f)) {
		m_estate = State_EDamage;
	}
}
void Enemy::Update()
{
	switch (m_estate)
	{
	case State_LeftMove:
     LeftMove();
	
		break;
	case State_RigthMove:
		RigthMove();
	
		break;
	case State_Tracking:
		Tracking();
		
		break;
	case State_EDamage:
		EnemyDeth = true;
		break;
	}
	
	    //m_moveSpeed.y -= 1700.0f * (1.0f / 60.0f);
		m_charaCon.SetPosition(m_position);
		m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
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