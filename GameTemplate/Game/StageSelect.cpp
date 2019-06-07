#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"

StageSelect::StageSelect()
{	
	m_model.Init(L"Assets/modelData/Stage01.cmo");
	m_model1.Init(L"Assets/modelData/Island.cmo");
	m_sprite.Init(L"Resource/sprite/StageSelect.dds", 1280, 720);
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	g_camera3D.SetPosition({ 0.0f,40.0f,100.0f });
	g_camera3D.SetTarget({0.0f,0.0f,0.0f});
	g_camera3D.SetFar(1000.0f);
	g_camera3D.Update();

}


StageSelect::~StageSelect()
{
}

void StageSelect::Update()
{

		CQuaternion qrot;
		qrot.SetRotationDeg(CVector3::AxisY(), 1.0f);
		m_model.UpdateWorldMatrix(m_position, m_rotation, { 0.02f,0.02f,0.02f });
		m_model1.UpdateWorldMatrix(m_position1, m_rotation1, { 0.01f,0.01f,0.01f });
		if (m_fontsize >= 1.0f)
		{
			m_fontsize -= 0.2f;
		}
	switch (m_select)
	{
	case State_Stage01:
		g_currentScene->SetSceneNo(1);

		m_rotation.Multiply(qrot);
		if (g_pad[0].IsTrigger(enButtonRight) == true)
		{
			flag = true;
		}
		if (flag == true) {
			m_position.x += 5.0f;
			m_position1.x += 5.0f;
			if (m_position.x >= 300.0f) {
				flag = false;
				m_select = State_Stage02;
			}
		}
		if (g_pad[0].IsTrigger(enButtonA) && g_fade->GetState() == Fade::idel) {

			//スタートの条件になったのでフェードを開始する
			g_fade->Fadein();
			StratFlag = true;

		}
		else if (StratFlag == true && g_fade->GetState() == Fade::idel)
		{
			g_currentScene = new Game;
			//m_titlebgm.Stop();
			g_fade->Fadeout();
			delete this;
		}

		if (g_pad[0].IsTrigger(enButtonB) == true)
		{
			m_select = State_Title;
		}
		break;
	case State_Stage02:
		g_currentScene->SetSceneNo(2);
		m_rotation1.Multiply(qrot);
		if (g_pad[0].IsTrigger(enButtonLeft) == true)
		{
			flag = true;
		}
		if (flag == true) {
			m_position.x -= 5.0f;
			m_position1.x -= 5.0f;
			if (m_position.x <= 0.0f) {
				flag = false;
				m_select = State_Stage01;
			}
		}
		if (g_pad[0].IsTrigger(enButtonA) && g_fade->GetState() == Fade::idel) {

			//スタートの条件になったのでフェードを開始する
			g_fade->Fadein();
			StratFlag = true;

		}
		else if (StratFlag == true && g_fade->GetState() == Fade::idel)
		{
			
			g_currentScene = new Game;
			g_fade->Fadeout();
			delete this;
		}
		if (g_pad[0].IsTrigger(enButtonB) == true)
		{
			m_select = State_Title;
		}
		break;
	case State_Title:
		g_currentScene->SetSceneNo(1);
		if (StratFlag == false && g_fade->GetState() == Fade::idel) {

			//スタートの条件になったのでフェードを開始する
			g_fade->Fadein();
			StratFlag = true;

		}
		else if (StratFlag == true && g_fade->GetState() == Fade::idel)
		{

			g_currentScene = new Title;
			g_fade->Fadeout();
			delete this;
		}
		break;
	}

}

void StageSelect::Draw()
{

	g_graphicsEngine->ChangeBackBaffer();
	m_sprite.Draw();
	m_font.BeginDraw();
	swprintf_s(moji, L"STAGE%d", g_currentScene->GetSceneNo());
	m_font.Draw
	(
		moji,		//表示する文字列。
		{ -100.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 1.0f,0.0f,0.0f,1.0f },
		m_mojiscale,
		m_fontsize,
		{ 0.0f,1.0f }
	);
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_model1.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	m_font.EndDraw();
}