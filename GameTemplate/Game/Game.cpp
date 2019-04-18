#include "stdafx.h"
#include "Game.h"
#include "Player.h"
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



Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	m_stage = new Stage(StageNo++);
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);	
	m_goal.SetPlayer(&m_player);
	m_stagebgm.Init(L"Assets/sound/stagebgm.wav");
	m_kirakirase.Init(L"Assets/sound/kirakira.wav");
	m_kirakirase.SetVolume(0.4f);
	m_stagebgm.SetVolume(0.5f);
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
	
	delete m_stage;
		if (m_frameBufferRenderTargetView != nullptr) {
			m_frameBufferRenderTargetView->Release();
		}
		if (m_frameBufferDepthStencilView != nullptr) {
			m_frameBufferDepthStencilView->Release();
		}
}

void Game::Update()
{
	switch (m_gstate)
	{
	case State_Default:
		//プレイヤーの更新。
		m_player.Update();
		//カメラの更新
		m_gameCamera.Update();
		m_hp.Update();
		m_stage->Update();
		m_stagebgm.Play(true);
		if ( m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 0 ) {
			
			//ゴールを更新
			m_goal.Update();	
		}
		if (m_player.GetZanki() <= 0 || m_time.GetAllSeconds() >= GAMETIME) {
		
			m_gstate = State_GameOver;
		}
		if (m_goal.GetGFlag() == true)
		{
			GoalCount++;
			Goal = true;
			if (StageNo <= 1 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
					m_gstate = State_StageChange /*State_TitleChange*/;
				}
				if (g_pad[0].IsPress(enButtonB) == true)
				{
					m_gstate = State_TitleChange;
				}
			}
			if (StageNo > 1 && StageNo <= 2 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
				
					m_gstate = State_TitleChange;
				}
			}
		}
		break;
	case State_StageChange:
		//現在のステージを消して次のステージを呼ぶ
		m_goal.SetGoalFlag(false);
		delete m_stage;
		m_stage = new Stage(StageNo++);
		Goal = false;
		GoalCount = 0;
		m_gstate = State_Default;
		break;
	case State_TitleChange:
		StageNo = 0;
		g_currentScene = new Title;
		delete this;
		break;
	case State_GameOver:
		m_over.Update();

		if (g_pad[0].IsTrigger(enButtonA))
		{
			
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
void Game::Draw()
{
	m_font.BeginDraw();	//フォントの描画開始。

	////レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget,m_mainRenderTarget.GetViewport());
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.7f, 1.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);

	//プレイヤーの描画。
	m_player.Draw();
	//ステージの描画
	m_stage->Draw();
	m_hp.Draw();

	if (m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 0) {
		//ゴールを表示
		if (SEflag == true) {
			m_kirakirase.Play(false);
			SEflag = false;
		}
		m_goal.Draw();
	}
	m_postEffect->Draw();
	//制限時間のタイマーをラップでストップさせる。
	m_time.TimerStop();
	if (m_goal.GetGFlag() == false) {
		swprintf_s(toubatu, L"コイン %d", m_stage->GetCoinCount());
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"スコア %d", m_stage->GetScore());
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -FRAME_BUFFER_W / 2.0f,300.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,1.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		
		//秒の計算をする
		 taim = (int)m_time.GetAllSeconds() % 201;
		swprintf_s(toubatu, L"残り時間%d秒", (GAMETIME - taim));		//表示用にデータを加工
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -200.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 1.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
	}


	if (m_goal.GetGFlag() == true && GoalCount >= 120.0f) {
		m_goalsprite.Draw();
		TimeScore = GAMETIME - taim;
		swprintf_s(toubatu, L"スコア %d", m_stage->GetScore());
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -200.0f , 100.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"タイムスコア %d", TimeScore);
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -300.0f , 30.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
		swprintf_s(toubatu, L"合計スコア %d", m_stage->GetScore() + TimeScore);
		m_font.Draw(
			toubatu,		//表示する文字列。
			{ -250.0f , -50.0f },			//表示する座標。0.0f, 0.0が画面の中心。
			{ 0.0f,0.0f,0.0f,1.0f },
			0.0f,
			1.5f,
			{ 0.0f,1.0f }
		);
	}
	//タイマーを再開させる
	m_time.TimerRestart();
	//文字表示の終了
	m_font.EndDraw();
	if (m_gstate == State_GameOver) {

		m_over.Draw();
	}
	
}