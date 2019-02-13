#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "level/Level.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Scaffold.h"
#include "Goal.h"
#include "Stage.h"
#include "Coin.h"
#include "Title.h"
#include "graphics/ShadowMap.h"
#include "graphics/Camera.h"


Game* g_game = nullptr;

Game::Game()
{
	g_game = this;
	m_stage = new Stage(No++);
	//static int count = 0;
	m_goalsprite.Init(L"Resource/sprite/kari.dds", 1280, 720);
	m_gameCamera.SetPlayer(&m_player);
	m_goal.SetPlayer(&m_player);
	m_soundEngine.Init();
	/*m_bgm.Init(L"Assets/sound/coinGet.wav");
	m_bgm.Play(true);*/
	m_coinse.Init(L"Assets/sound/coinGet.wav");
	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
}


Game::~Game()
{
	
	g_currentScene = new Title;
	//動的に確保したインスタンスを破棄。

		delete &m_goal;
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
		m_soundEngine.Update();
		//プレイヤーの更新。
		m_player.Update();
		//カメラの更新
		m_gameCamera.Update();
		m_stage->Update();
		//ポストエフェクトの更新。
		m_postEffect.Update();
		if (m_goal.GetGFlag() == false) {
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

					m_gstate = State_StageChange;
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
		delete m_stage;
		break;
	}

}
void Game::Draw()
{
	//プレイヤーの描画。
	m_player.Draw();
	//ステージの描画
	m_stage->Draw();
	if (m_goal.GetGFlag() == true && GoalCount >= 120.0f) {
		m_goalsprite.Draw();

	}
	if (m_goal.GetGFlag() == false) {
		//ゴールを表示
		m_goal.Draw();
	}
	//ポストエフェクトの描画。
	m_postEffect.Draw();
}