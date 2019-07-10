#include "stdafx.h"
#include "Enemy.h"
#include "Player/Player.h"
#include "graphics/ShadowMap.h"
#include "Stage.h"

using namespace std;
Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/kkk.cmo");

	m_animationClips[enAnimationClip_walk].Load(L"Assets/animData/enemywalk1.tka");
	m_animationClips[enAnimationClip_walk].SetLoopFlag(true);

	m_animationClips[enAnimation_Damage].Load(L"Assets/animData/enemydeth.tka");
	m_animationClips[enAnimation_Damage].SetLoopFlag(false);

	m_damagese.Init(L"Assets/sound/punch-middle2.wav");
	m_damagese.SetVolume(0.5f);
	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		enAnimationClip_Num					//アニメーションクリップの数。
	);

	m_enemyEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/hit.efk");

	//キャラコン設定
	m_charaCon.Init(50.0f, 40.0f, m_position);
}


Enemy::~Enemy()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void Enemy::Move()
{
	m_kari = m_front * 5.0f;
	idoutime++;
	m_position += m_kari;
	//Y方向の移動速度は重力加速を行う。
	m_moveSpeed.y -= 1800.0f * (1.0f / 60.0f);

	//m_rotation.SetRotationDeg(CVector3::AxisY(), 90.0f*i);
	if (idoutime >= 40) {
		idoutime = 0;
		CQuaternion qrto;
		qrto.SetRotationDeg(CVector3::AxisY(), 180.0f);
		m_rotation.Multiply(qrto);
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
}
void Enemy::Damage()
{

	m_up = { m_mRot.m[1][0] ,m_mRot.m[1][1] ,m_mRot.m[1][2] };
	CVector3 springForward = CVector3::AxisY();
	m_rotation.Multiply(springForward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_player->GetPosition() - m_position;
	CVector3 toEnemyDir2 = m_player->GetAttackPos() - m_position;
	//エネミーまでの距離を求めておく。
	float toEnemyLen = toEnemyDir.Length();
	float toEnemyLen2 = toEnemyDir2.Length();
	//正規化
	toEnemyDir.Normalize();
	
	//springForwardとtoEnemyDirとの内積を計算する。
	float d = toEnemyDir.Dot(m_up);
	//内積の結果をacos関数に渡して、springForwardとtoEnemyDirのなす角を求める。
	float angle = acosf(d);
	angle = CMath::RadToDeg(angle);

	if (toEnemyLen <= 60.0f &&  angle <= 65.0f ) {
		m_estate = State_EDamage;
		if (g_pad[0].IsTrigger(enButtonA)) {
			m_player->AddMoveSpeed({0.0f,700.0f,0.0f});
		}
	}
	if (toEnemyLen2 <= 60.0f)
	{
		punchflag = true;
		m_damagese.Play(false);
		m_estate = State_EDamage;
	}
}
void Enemy::EnemyAnimation()
{
	if (m_estate == State_Move)
	{
		m_animation.Play(enAnimationClip_walk, 0.2f);
	}
	if (m_estate == State_EDamage)
	{
		m_animation.Play(enAnimation_Damage, 0.2f);
	}
}
void Enemy::Update()
{
	
	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_front = { m_mRot.m[2][0] ,m_mRot.m[2][1] ,m_mRot.m[2][2] };
	Damage();
	EnemyAnimation();
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
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.y = 0.0f;
		AnimPlayTime++;
		if (punchflag == true) {
			m_position -= m_kari * 5.0f;

		}
		if (AnimPlayTime >= 10) {
			punchflag = false;
			
		}
		if (AnimPlayTime >= 50) {
			EnemyDeth = true;
			m_enemyEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_enemyEffect, m_position.x, m_position.y, m_position.z);
			AnimPlayTime = 0;
		}
		break;
	}
	if (m_estate != State_EDamage) {
		m_moveSpeed.y -= 1800.0f /** (1.0f / 60.0f)*/;
	}
	m_charaCon.SetPosition(m_position);
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_model.SetShadowReciever(true);
	//ワールド行列の更新
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 60.0f);

}

void Enemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}