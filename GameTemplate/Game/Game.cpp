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
	m_stage = new Stage(No++);
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);	
	m_goal.SetPlayer(&m_player);
	m_coinse.Init(L"Assets/sound/coinGet.wav");
	m_stagebgm.Init(L"Assets/sound/bgm_00.wav");
	m_kirakirase.Init(L"Assets/sound/kirakira.wav");
	m_kirakirase.SetVolume(0.4f);
	m_stagebgm.SetVolume(0.5f);
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
	
	g_currentScene = new Title;
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
	//	m_stagebgm.Play(true);
		if ( m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 5 ) {
			//ゴールを更新
			m_goal.Update();	
		}
		if (CoinGetFlag == true) {
			//コインの音を鳴らす
			m_coinse.Play(false);
			CoinGetFlag = false;
		}
		if (m_goal.GetGFlag() == true)
		{
			GoalCount++;
			Goal = true;
			if (No <= 1 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {

					m_gstate = State_TitleChange;
				}
			}
			if (No > 1 && No <= 2 && GoalCount >= 120.0f) {

				if (g_pad[0].IsPress(enButtonA) == true) {
					m_gstate = State_TitleChange;
				}
			}
		}
		break;
	case State_StageChange:
		//現在のステージを消して次のステージを呼ぶ
		delete m_stage;
		m_stage = new Stage(No++);

		m_goal.SetGFlag(false);
		Goal = false;
		GoalCount = 0;
		m_gstate = State_Default;
		break;
	case State_TitleChange:
		//g_currentScene = new Title;
		//delete m_stage;
		delete this;
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

	//g_graphicsEngine->ChangeBackBaffer();
	//プレイヤーの描画。
	m_player.Draw();
	//ステージの描画
	m_stage->Draw();
	m_hp.Draw();
	if (m_goal.GetGFlag() == true && GoalCount >= 120.0f) {
		m_goalsprite.Draw();

	}
	if (m_goal.GetGFlag() == false && m_stage->GetEnemyCount() == 5) {
		//ゴールを表示
		if (SEflag == true) {
			m_kirakirase.Play(false);
			SEflag = false;
		}
		m_goal.Draw();
	}
	m_postEffect->Draw();
	wchar_t toubatu[256];
	swprintf_s(toubatu, L"コイン %d",m_stage->GetCoinCount());
	m_font.Draw(
		toubatu,		//表示する文字列。
		{ -FRAME_BUFFER_W / 2.0f,FRAME_BUFFER_H / 2.0f },			//表示する座標。0.0f, 0.0が画面の中心。
		{ 0.0f,1.0f,0.0f,1.0f },
		0.0f,
		1.5f,
		{ 0.0f,1.0f }
	);

	m_font.EndDraw();
}