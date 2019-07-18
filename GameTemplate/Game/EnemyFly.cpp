#include "stdafx.h"
#include "EnemyFly.h"
#include "Player/Player.h"
#include "graphics/ShadowMap.h"
#include "Stage.h"


EnemyFly::EnemyFly(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/StoneMonster.cmo");

	m_damagese.Init(L"Assets/sound/punch-middle2.wav");
	m_damagese.SetVolume(0.5f);

	m_enemyEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/hit.efk");

	//キャラコン設定
	m_charaCon.Init(50.0f, 40.0f, m_position);
}


EnemyFly::~EnemyFly()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void EnemyFly::Move()
{
	m_kari = m_front * 5.0f;
	idoutime++;
	m_position += m_kari;
	if (idoutime >= 60) {
		idoutime = 0;
		CQuaternion qrto;
		qrto.SetRotationDeg(CVector3::AxisY(), 180.0f);
		m_rotation.Multiply(qrto);
	}
}
void EnemyFly::Damage()
{


	CVector3 toEnemyDir2 = m_player->GetAttackPos() - m_position;
	float toEnemyLen2 = toEnemyDir2.Length();
	if (toEnemyLen2 <= 60.0f)
	{
		punchflag = true;
		m_damagese.Play(false);
		m_estate = State_EDamage;
	}
}
void EnemyFly::Update()
{

	m_mRot.MakeRotationFromQuaternion(m_rotation);
	m_front = { m_mRot.m[2][0] ,m_mRot.m[2][1] ,m_mRot.m[2][2] };
	Damage();
	switch (m_estate)
	{
	case State_Move:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		Move();
		if (m_position.y <= -500.0f) {

			m_estate = State_EDamage;

		}
		break;
	case State_EDamage:
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.y = 0.0f;
		AnimPlayTime++;
		if (punchflag == true){
			CVector3 toEnemyDir = m_player->GetPosition() - m_position;
			toEnemyDir.Normalize();
			m_position -= toEnemyDir * 50.0f;

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
	//m_moveSpeed.y -= 1800.0f /** (1.0f / 60.0f)*/;
	m_charaCon.SetPosition(m_position);
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_model.SetShadowReciever(true);
	//ワールド行列の更新
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void EnemyFly::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}