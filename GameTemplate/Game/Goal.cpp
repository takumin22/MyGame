#include "stdafx.h"
#include "Goal.h"
#include "Player.h"



Goal::Goal()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/star1.cmo",enFbxUpAxisZ);
	m_position.z = 150.0f;
	m_position.y = 100.0f;
	m_position.x = -100.0f;
}


Goal::~Goal()
{

}
void Goal::GoalGet()
{
	//ゴールからプレイヤーまでのベクトルを求める
	CVector3 toGoalDir = m_position - m_player->GetPosition();
	//ゴールまでの距離を求めておく。
	float toGoalLen = toGoalDir.Length();
	if (toGoalLen <= 80.0f) {
		GetFlag = true;
		
	}
	else {
		GetFlag = false;
	}
}

void Goal::Update()
{
	GoalGet();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
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