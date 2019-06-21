#include "stdafx.h"
#include "RedCoin.h"
#include "Player/Player.h"
#include "Game.h"
#include "graphics/ShadowMap.h"
#include "Gate.h"


RedCoin::RedCoin(CVector3 pos, CQuaternion rot, Player* player):
m_position(pos),
m_rotation(rot),
m_player(player)
{
	m_model.Init(L"Assets/modelData/RedCoin.cmo", enFbxUpAxisZ, { 3.0f,3.0f,3.0f,1.0f });
	m_model.SetAmbientLight(ambientColor);

	m_coinEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/coineffect.efk");
}


RedCoin::~RedCoin()
{
	g_shadowMap->UnregistShadowCaster(&m_model);
}

void RedCoin::CoinGet()
{
	//コインからプレイヤーに伸びるベクトルを求める。
	CVector3 toCoin = m_player->GetPosition() - m_position;
	//コインまでの距離を求める
	float len = toCoin.Length();
	if (len <= 70.0f) {
		flag = true;
	}
	if (flag == true)
	{
		rotspeed += 10.0f;
		m_position.y += 10.0f;
		m_scale.y -= 0.08f;
		m_scale.z -= 0.08f;
		CoinTime++;


	}
	if (CoinTime >= 10) {
		CoinGetFlag = true;
		//エフェクトを再生する。
		m_coinEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_coinEffect, m_position.x, m_position.y, m_position.z);
		flag = false;
		CoinTime = 0;
	}
}

void RedCoin::Update()
{


	CoinGet();
	//コインを回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), rotspeed);
	m_rotation.Multiply(qRot);
	//ワールド行列の更新
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void RedCoin::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}