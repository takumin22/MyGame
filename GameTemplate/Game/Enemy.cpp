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
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/kkk.cmo");
	//キャラコン設定
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
		//Y方向の移動速度は重力加速を行う。
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
    //Y方向の移動速度は重力加速を行う。
	m_moveSpeed.y -= 1700.0f * (1.0f / 60.0f);
	m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f);
	if (m_position.x >= 162.0f) {
		m_estate = State_RigthMove;
	}
	Search();

}
void Enemy::Search() 
{
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_position - m_player->GetPosition();
	//エネミーまでの距離を求めておく。
	float toEnemyLen = toEnemyDir.Length();
	if (toEnemyLen < 200.0f) {
		m_estate = State_Tracking;
	}
}
void Enemy::Tracking()
{
	
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayer = m_player->GetPosition() - m_position;
	//プレイヤーまでの距離を求める
	float len = toPlayer.Length();
	//正規化
	toPlayer.Normalize();
	m_moveSpeed = toPlayer * 200.0f;
	m_moveSpeed.y += -20.0f * (1.0f / 60.0f);
	if (len > 200.0f) {;
		m_estate = State_LeftMove;
	}
	Damage();
	//向き
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy::Damage()
{
	CVector3 springForward = CVector3::AxisY();
	m_rotation.Multiply(springForward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_position - m_player->GetPosition()  ;
	//エネミーまでの距離を求めておく。
	float toEnemyLen = toEnemyDir.Length();
	//正規化
	toEnemyDir.Normalize();
	//springForwardとtoEnemyDirとの内積を計算する。
	float d = springForward.Dot(toEnemyDir);
	//内積の結果をacos関数に渡して、springForwardとtoEnemyDirのなす角を求める。
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
		//ワールド行列の更新
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