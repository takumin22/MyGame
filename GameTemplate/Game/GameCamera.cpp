#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Goal.h"
#include "Game.h"

GameCamera::GameCamera()
{

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
		newTarget.y += 20.0f;
		CVector3 toCameraPosOld = toCameraPos;
		//パッドの入力を使ってカメラを回す。
		float x = g_pad[0].GetRStickXF();
		float y = g_pad[0].GetRStickYF();
		//Y軸周りの回転
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 5.0f * x);
		qRot.Multiply(toCameraPos);
		//X軸周りの回転。
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 5.0f * y);
		qRot.Multiply(toCameraPos);
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();


		//カメラからプレイヤーに向かうベクトルを計算する。
		CVector3 toPlayer = g_camera3D.GetPosition()-m_player->GetPosition();
		//プレイヤーに向かうベクトルを正規化する(大きさ1にする)。
		toPlayer.Normalize();
		//前方方向と、プレイヤーへの向きベクトルの内積を計算する。
		float forward = toPlayer.Dot((m_player->GetForWard()));
		float tatemuki = toPlayer.Dot((m_player->GetUp()));
		//内積の結果はcosθになるため、なす角θを求めるためにacosを実行する。③
		forward = acosf(Acos(forward));
		forward = CMath::RadToDeg(forward);
		tatemuki = acosf(Acos2(tatemuki));
		tatemuki = CMath::RadToDeg(tatemuki);

	if (g_game->GetGoal() == true)
	{	
		k = true;

	}	
	else if (g_game->GetGoal() == false) 
	{
		k = false;
	}
	if (k == true && forward >= 25.0f ) {
		qRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
		qRot.Multiply(toCameraPos);

	}	
	//if (k == true && tatemuki >= 90.0f)
	//{
	//	qRot.SetRotationDeg(CVector3::AxisZ(), 5.0f);
	//	qRot.Multiply(toCameraPos);

	//}

		if (toPosDir.y < 0.0f) {
			//カメラが上向きすぎ。
			toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//カメラが下向きすぎ。
			toCameraPos = toCameraPosOld;
		}
		//新しい視点を計算する。
		auto newPositin = newTarget + toCameraPos;

		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPositin);
		g_camera3D.Update();
}
