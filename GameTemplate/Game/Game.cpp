#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Scaffold.h"
#include "Goal.h"
#include "Stage.h"
#include "PostEffect.h"
#include "Coin.h"
#include "Title.h"
#include "graphics/ShadowMap.h"
#include "graphics/Camera.h"
#include "sky.h"


Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	if (g_currentScene->GetSceneNo() == 1)
	{
		StageNo = 0;
	}
	else if (g_currentScene->GetSceneNo() == 2)
	{
		StageNo = 1;
	}
	m_stage = new Stage(StageNo++);
	m_cubemap = new sky;
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);
	m_goal.SetPlayer(&m_player);
	m_point.SetPlayer(&m_player);
	m_stagebgm.Init(L"Assets/sound/stagebgm.wav");
	m_kirakirase.Init(L"Assets/sound/kirakira.wav");
	m_kirakirase.SetVolume(0.5f);
	m_stagebgm.SetVolume(0.5f);
	m_stagebgm.Play(true);
	m_time.TimerStart();
	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_postEffect = new PostEffect;
	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_postEffect->SetPost(m_mainRenderTarget.GetRenderTargetSRV());
}


Game::~Game()
{
	//delete &m_time;
	delete m_stage;
}

void Game::Update()
{

	m_cubemap->Update();
	switch (m_gstate)
	{
	case State_Default:
		continuityflug = false;
		//プレイヤーの更新。
		m_player.Update();
		//カメラの更新
		m_gameCamera.Update();
		m_hp.Update();
		m_stage->Update();
		m_point.Update();
		if (g_pad[0].IsTrigger(enButtonStart) == true)
		{
			m_gstate = State_Pose;
		}
		if (m_stage->GetRedCoinCount() == 3)
		{

			if (SEflag == true) {
				m_kirakirase.Play(false);
				SEflag = false;
			}
		}
		if (m_goal.GetGFlag() == false && m_stage->GetRedCoinCount() >= 3) {

			//ゴールを更新
			m_goal.Update();
		}
		if (m_player.GetZanki() <= 0 || m_time.GetAllSeconds() >= GAMETIME) {
			if (ChangeFlag == false && g_fade->GetState() == Fade::idel) {
				g_fade->Fadein();
				ChangeFlag = true;

			}
			if (ChangeFlag == true && g_fade->GetState() == Fade::idel)
			{
				g_fade->Fadeout();
				ChangeFlag = false;
				m_gstate = State_GameOver;
			}

		}
		if (m_goal.GetGFlag() == true)
		{
			GoalCount++;
			Goal = true;
			m_time.TimerStop();
			if (GoalCount >= 120.0f) {
				m_gstate = State_GameClear;
			}
		}
		break;
	case State_Pose:
		m_pose.Updata();
		if (g_pad[0].IsTrigger(enButtonA) == true && m_pose.GetFlag() == false)
		{
			m_gstate = State_Default;
		}
		if (ChangeFlag == false && m_pose.GetFlag() == true && g_fade->GetState() == Fade::idel) {
			g_fade->Fadein();
			ChangeFlag = true;

		}
		if (ChangeFlag == true && g_fade->GetState() == Fade::idel)
		{
			g_fade->Fadeout();
			ChangeFlag = false;
			m_gstate = State_TitleChange;
		}
		break;
	case State_StageChange:
		//現在のステージを消して次のステージを呼ぶ
		m_goal.SetGoalFlag(false);
		delete m_stage;
		m_player.VecterCler();
		m_time.SetAllelapsed(0.0);
		m_stage = new Stage(StageNo++);
		Goal = false;
		flag = false;
		m_cler.Relese();
		GoalCount = 0;
		m_gstate = State_Default;
		break;
	case State_TitleChange:
		StageNo = 0;
		g_currentScene = new Title;
		delete this;
		break;
	case State_GameClear:
		m_cler.Update();
		if (StageNo <= 1) 
		{
			if (g_pad[0].IsPress(enButtonA) == true) {
				taim = 0;
				if (g_fade->GetState() == Fade::idel) {
					g_fade->Fadein();
					ChangeFlag = true;
				}
			}
			if (ChangeFlag == true && g_fade->GetState() == Fade::idel) {
				g_fade->Fadeout();
				ChangeFlag = false;
				m_gstate = State_StageChange;
			}
		}
		else if (StageNo > 1 && StageNo <= 2)
		{
			if (g_pad[0].IsPress(enButtonA) == true && g_fade->GetState() == Fade::idel) {
				g_fade->Fadein();
				ChangeFlag = true;

			}
			if (ChangeFlag == true && g_fade->GetState() == Fade::idel)
			{
				g_fade->Fadeout();
				ChangeFlag = false;
				m_gstate = State_TitleChange;
			}
		}
		break;
	case State_GameOver:
		m_over.Update();
		if (m_over.Getflag() == true && g_fade->GetState() == Fade::fadeout) {
			continuityflug = true;
			m_time.SetAllelapsed(0.0);
			m_over.OverClear();
			m_gstate = State_Default;
		}
		else if (m_over.Gettitleflag() == true && g_fade->GetState() == Fade::fadeout) {
			m_over.OverClear();
			m_gstate = State_TitleChange;
		}
		break;
	}
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}
void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}
void Game::GameFont()
{
	if (m_goal.GetGFlag() == false) {
		swprintf_s(toubatu, L"コイン%02d", m_stage->GetCoinCount());
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			m_fontscale,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"残機%02d", m_player.GetZanki());
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,300.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			m_fontscale,
			{ 0.0f,1.0f }
		);
		//秒の計算をする
		if (m_gstate == !State_Pose) {
			taim = (int)m_time.GetAllSeconds() % 201;
		}
		swprintf_s(toubatu, L"残り時間%03d秒", (GAMETIME - taim));		//表示用にデータを加工
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -200.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			m_fontscale,
			{ 0.0f,1.0f }
		);
	}

	
	if (m_gstate == State_GameClear && m_cler.GetSpritePos().y <= 10.0f) {

		if (flag == false) {
			TimeScore = GAMETIME - taim;
			flag = true;
		}
	
	}
}
void Game::Draw()
{
	m_font.BeginDraw();	//フォントの描画開始。

						////レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, m_mainRenderTarget.GetViewport());
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	//プレイヤーの描画。
	m_player.Draw();

	//ステージの描画
	m_stage->Draw();
	m_cubemap->Draw();
	m_hp.Draw();
	m_point.Draw();
	if (m_gstate == State_Pose) {
		m_pose.Draw();
	}
	if (m_goal.GetGFlag() == false && m_stage->GetRedCoinCount() >= 3) {
		//ゴールを表示
		m_goal.Draw();
	}
	if (m_gstate == State_GameClear)
	{
		m_cler.Darw();
	}
	m_postEffect->Draw();

	//制限時間のタイマーをラップでストップさせる。
	m_time.TimerStop();
	GameFont();
	//タイマーを再開させる
	m_time.TimerRestart();
	//文字表示の終了
	m_font.EndDraw();
	if (m_gstate == State_GameOver) {
		m_over.Draw();
	}

}