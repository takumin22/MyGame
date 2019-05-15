#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Goal.h"
#include "Game.h"

GameCamera::GameCamera()
{

	m_characon.Init(0.00001f, 0.00001f, { 0.0f, 2100.0f, 300.0f });
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
		newTarget.y += 100.0f;
		CVector3 toCameraPosOld = toCameraPos;
		//�p�b�h�̓��͂��g���ăJ�������񂷁B
		float x = g_pad[0].GetRStickXF() *5.0f;
		float y = g_pad[0].GetRStickYF() *5.0f;
		//Y������̉�]
		CQuaternion qRot;
		qRot.SetRotationDeg(g_camera3D.GetUp(), x);
		qRot.Multiply(toCameraPos);
		//X������̉�]�B
		CQuaternion qrot;
		qrot.SetRotationDeg(g_camera3D.GetRight(), y);
		qrot.Multiply(toCameraPos);
		CVector3 toPosDir = toCameraPos;
		toPosDir.Normalize();
		float angle = toPosDir.Dot(g_camera3D.GetUp());
		angle = acosf(Acos(angle));
		angle = CMath::RadToDeg(angle);


		//�J��������v���C���[�Ɍ������x�N�g�����v�Z����B
		CVector3 toPlayer = g_camera3D.GetPosition()-m_player->GetPosition();
		//�v���C���[�Ɍ������x�N�g���𐳋K������(�傫��1�ɂ���)�B
		toPlayer.Normalize();
		//�O�������ƁA�v���C���[�ւ̌����x�N�g���̓��ς��v�Z����B
		float forward = toPlayer.Dot((m_player->GetForWard()));
		//���ς̌��ʂ�cos�ƂɂȂ邽�߁A�Ȃ��p�Ƃ����߂邽�߂�acos�����s����B�B
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
		//	//�J����������������B
		//	toCameraPos = toCameraPosOld;
		//	qRot.SetRotationDeg(g_camera3D.GetUp(), x);
		//	qRot.Multiply(toCameraPos);
		//}
		else if (angle  < 30.0f) {
			//�J�����������������B
			toCameraPos = toCameraPosOld;

		}
		//�V�������_���v�Z����B
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
