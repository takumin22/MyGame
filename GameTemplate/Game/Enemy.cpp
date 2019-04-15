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
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/kkk.cmo");
	//キャラコン設定
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
		//Y方向の移動速度は重力加速を行う。
		m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);
		m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f*i);
		if (idoutime>= 40) {
			idoutime = 0;
			i *= -1;
		}
}
void Enemy::Search() 
{
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_player->GetPosition() - m_position;
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
	m_moveSpeed.y += -1800.0f * (1.0f / 60.0f);
	if (len > 200.0f) {
		m_estate = State_Move;
	}
	
	//向き
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
	//m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}
void Enemy::Damage()
{
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_up = { m_mRot.m[1][0] ,m_mRot.m[1][1] ,m_mRot.m[1][2] };
	CVector3 springForward = CVector3::AxisY();
	m_rotation.Multiply(springForward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_player->GetPosition()  -m_position ;
	//エネミーまでの距離を求めておく。
	float toEnemyLen = toEnemyDir.Length();
	//正規化
	toEnemyDir.Normalize();
	//springForwardとtoEnemyDirとの内積を計算する。
	float d = toEnemyDir.Dot(m_up);
	//内積の結果をacos関数に渡して、springForwardとtoEnemyDirのなす角を求める。
	float angle = acosf(d);
	 angle = CMath::RadToDeg(angle);


	////カメラからプレイヤーに向かうベクトルを計算する。
	//CVector3 toPlayer = g_camera3D.GetPosition() - m_player->GetPosition();
	//float toEnemyDir = toPlayer.Length();
	////プレイヤーに向かうベクトルを正規化する(大きさ1にする)。
	//toPlayer.Normalize();
	////前方方向と、プレイヤーへの向きベクトルの内積を計算する。
	//float forward = toPlayer.Dot((m_player->GetUp()));
	////内積の結果はcosθになるため、なす角θを求めるためにacosを実行する。③
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