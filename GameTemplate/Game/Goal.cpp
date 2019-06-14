#include "stdafx.h"
#include "Goal.h"
#include "Player/Player.h"
#include "Stage.h"
#include "Game.h"


Goal::Goal()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/star1.cmo", enFbxUpAxisZ ,{2.5f,2.5f,2.5f,1.0f});

	m_starEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/effect/coineffect.efk");
}


Goal::~Goal()
{
	
	g_shadowMap->UnregistShadowCaster(&m_model);

}
void Goal::GoalGet()
{
	//ゴールからプレイヤーまでのベクトルを求める
	CVector3 toGoalDir = m_position - m_player->GetPosition();
	//ゴールまでの距離を求めておく。
	float toGoalLen = toGoalDir.Length();
	if (toGoalLen <= 80.0f) {
		flag = true;	
	}
	if (flag == true)
	{
		srot += 0.5f;
		m_position.y += 1.5;
		StarTime++;
	}

	if (StarTime >= 45.0f)
	{
		GetFlag = true;
		//エフェクトを再生する。
		m_starEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_starEffect, m_position.x, m_position.y, m_position.z);
		StarTime = 0;
		flag = false;
	}
}

void Goal::Update()
{

		GoalGet();
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), srot);
		m_rotation.Multiply(qRot);
		g_shadowMap->RegistShadowCaster(&m_model);
		//ワールド行列の更新
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	
}

void Goal::Draw()
{

		m_model.Draw(
			enRenderMode_Normal,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	
}