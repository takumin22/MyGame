#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Goal.h"
#include "Game.h"

GameCamera::GameCamera()
{

	m_characon.Init(0.00001f, 0.00001f, { 0.0f, 2100.0f, 300.0f });
	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 210.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{	



	//現在の注視点から視点へのベクトルを求めるよ。
		auto toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		auto newTarget = m_player->GetPosition();
		//Y方向にちょっと上げる。
		newTarget.y += 100.0f;
		CVector3 toCameraPosOld = toCameraPos;
		//パッドの入力を使ってカメラを回す。
		float x = g_pad[0].GetRStickXF() *5.0f;
		float y = g_pad[0].GetRStickYF() *5.0f;
		//Y軸周りの回転
		CQuaternion qRot;
		qRot.SetRotationDeg(g_camera3D.GetUp(), x);
		qRot.Multiply(toCameraPos);
		//X軸周りの回転。
		CQuaternion qrot;
		qrot.SetRotationDeg(g_camera3D.GetRight(), y);
		qrot.Multiply(toCameraPos);
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();
		float angle = toPosDir.Dot(g_camera3D.GetUp());
		angle = acosf(Acos(angle));
		angle = CMath::RadToDeg(angle);


		//カメラからプレイヤーに向かうベクトルを計算する。
		CVector3 toPlayer = g_camera3D.GetPosition()-m_player->GetPosition();
		//プレイヤーに向かうベクトルを正規化する(大きさ1にする)。
		toPlayer.Normalize();
		//前方方向と、プレイヤーへの向きベクトルの内積を計算する。
		float forward = toPlayer.Dot((m_player->GetForWard()));
		//内積の結果はcosθになるため、なす角θを求めるためにacosを実行する。③
		forward = acosf(Acos(forward));
		forward = CMath::RadToDeg(forward);

	if (g_game->GetGoal() == true)
	{	
		GoalCamera = true;

	}	
	else if (g_game->GetGoal() == false) 
	{
		GoalCamera = false;
	}
	if (GoalCamera == true && forward >= 25.0f ) {
		qRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
		qRot.Multiply(toCameraPos);

	}	

		//if (angle > 90.0f) {
		//	//カメラが上向きすぎ。
		//	toCameraPos = toCameraPosOld;
		//	qRot.SetRotationDeg(g_camera3D.GetUp(), x);
		//	qRot.Multiply(toCameraPos);
		//}
		else if (angle  < 30.0f) {
			//カメラが下向きすぎ。
			toCameraPos = toCameraPosOld;

		}
		//新しい視点を計算する。
		qRot.SetRotationDeg(g_camera3D.GetUp(), x);
		qRot.Multiply(toCameraPos);
		auto newPositin = CVector3::Zero();// = newTarget + toCameraPos;
		m_characon.SetPosition(newTarget);
		toCameraPos.Normalize();
		toCameraPos *= 300.0f;
		newPositin = m_characon.Execute(1.0f, toCameraPos);

		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPositin);
		g_camera3D.Update();
}
