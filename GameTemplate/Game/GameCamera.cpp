#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Goal.h"
#include "Game.h"

GameCamera::GameCamera()
{

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 210.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
}


GameCamera::~GameCamera()
{
}
void GameCamera::Update()
{	



	//���݂̒����_���王�_�ւ̃x�N�g�������߂��B
		auto toCameraPos = g_camera3D.GetPosition() - g_camera3D.GetTarget();
		auto newTarget = m_player->GetPosition();
		//Y�����ɂ�����Əグ��B
		newTarget.y += 20.0f;
		CVector3 toCameraPosOld = toCameraPos;
		//�p�b�h�̓��͂��g���ăJ�������񂷁B
		float x = g_pad[0].GetRStickXF();
		float y = g_pad[0].GetRStickYF();
		//Y������̉�]
		CQuaternion qRot;
		qRot.SetRotationDeg(CVector3::AxisY(), 5.0f * x);
		qRot.Multiply(toCameraPos);
		//X������̉�]�B
		CVector3 axisX;
		axisX.Cross(CVector3::AxisY(), toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 5.0f * y);
		qRot.Multiply(toCameraPos);
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();


		//�J��������v���C���[�Ɍ������x�N�g�����v�Z����B
		CVector3 toPlayer = g_camera3D.GetPosition()-m_player->GetPosition();
		//�v���C���[�Ɍ������x�N�g���𐳋K������(�傫��1�ɂ���)�B
		toPlayer.Normalize();
		//�O�������ƁA�v���C���[�ւ̌����x�N�g���̓��ς��v�Z����B
		float forward = toPlayer.Dot((m_player->GetForWard()));
		float tatemuki = toPlayer.Dot((m_player->GetUp()));
		//���ς̌��ʂ�cos�ƂɂȂ邽�߁A�Ȃ��p�Ƃ����߂邽�߂�acos�����s����B�B
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
			//�J����������������B
			toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.8f) {
			//�J�����������������B
			toCameraPos = toCameraPosOld;
		}
		//�V�������_���v�Z����B
		auto newPositin = newTarget + toCameraPos;

		g_camera3D.SetTarget(newTarget);
		g_camera3D.SetPosition(newPositin);
		g_camera3D.Update();
}
