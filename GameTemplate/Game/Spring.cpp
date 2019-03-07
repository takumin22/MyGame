#include "stdafx.h"
#include "Spring.h"
#include "Player.h"


Spring::Spring(CVector3 pos, CQuaternion rot, Player* player):
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
    //cmoファイルの読み込み
	m_model.Init(L"Assets/modelData/Spring.cmo");

	/*m_animationClips[enAnimationClip_spring].Load(L"Assets/animData/spring.tka");
	m_animationClips[enAnimationClip_spring].SetLoopFlag(true);*/

	//アニメーションの初期化。
	//m_animation.Init(
	//	m_model,			//アニメーションを流すスキンモデル。
	//						//これでアニメーションとスキンモデルが関連付けされる。
	//	m_animationClips,	//アニメーションクリップの配列。
	//	enAnimationClip_Num					//アニメーションクリップの数。
	//);
	//静的物理オブジェクトを作成
	m_phyStaticObject.CreateMeshObject(m_model, m_position, CQuaternion::Identity());
    m_model.UpdateWorldMatrix(m_position, m_rotation,m_scale);
}


Spring::~Spring()
{
	m_phyStaticObject.Releasehantei();
	g_shadowMap->UnregistShadowCaster(&m_model);
}
void Spring::SpringJump()
{
	//CVector3 springForward = CVector3::AxisY();
	//m_rotation.Multiply(springForward);
	////ジャンプ台からプレイヤーに伸びるベクトルを求める。
	//CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	////ジャンプ台までの距離を求めておく。
	//float toPlayerLen = toPlayerDir.Length();
	////正規化
	//toPlayerDir.Normalize();
	////springForwardとtoPlayerDirとの内積を計算する。
	//float d = springForward.Dot(toPlayerDir);
	////内積の結果をacos関数に渡して、springForwardとtoPlayerDirのなす角を求める。
	//float angle = acos(d);

}
void Spring::SpringAnimation()
{
	CVector3 springForward = CVector3::AxisY();
	//springからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_position - m_player->GetPosition();
	//springまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化
	toPlayerDir.Normalize();
	//springForwardとtoPlayerDirとの内積を計算する。
	float d = springForward.Dot(toPlayerDir);
	//内積の結果をacos関数に渡して、springForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);
	if (toPlayerLen <= 70.0f) {
		//m_player->SetMoveSpeed(1300.0f);
	}
	
}
void Spring::Update()
{
	//SpringAnimation();
	g_shadowMap->RegistShadowCaster(&m_model);
	m_model.SetShadowReciever(true);
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Spring::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}