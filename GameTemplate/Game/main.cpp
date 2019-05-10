#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include <algorithm>
#include "Stage.h"
#include "Title.h"
#include "Sprite.h"
#include "graphics/Camera.h"
#include "graphics/ShadowMap.h"
#include "PostEffect.h"
#include "Fade.h"
///////////////////////////////////////////////////////////////////
//クラスのインスタンスをグローバルな領域に置く場合は
//動的確保をしたほうが良い。
//なぜか？
//  ->アプリケーションが起動したときにコンストラクタが呼ばれるから。
//    ->なんの問題がある？
//      ->エンジンの初期化の前にコンストラクタが呼ばれると困る！
///////////////////////////////////////////////////////////////////

IScene* g_currentScene = nullptr;
ShadowMap* g_shadowMap = nullptr;
Fade* g_fade = nullptr;
//Game* g_game = nullptr;
///////////////////////////////////////////////////////////////////
//ゲームの更新処理。
//座標の更新とかの処理はここで呼び出すとよいかも？
///////////////////////////////////////////////////////////////////
void UpdateGame()
{
	
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	g_physics.Update();
	//フェードの更新
	g_fade->Update();
	//現在のシーンの更新。
	g_currentScene->Update();
	
}
///////////////////////////////////////////////////////////////////
// ゲームの描画処理。
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	
	

	//描画開始。
	g_graphicsEngine->BegineRender();


	//シャドウマップにレンダリング
	g_shadowMap->RenderToShadowMap();


	//現在のシーンの描画。
	g_currentScene->Draw();
	//フェードの描画
	g_fade->Draw();
	
	g_graphicsEngine->EffectUpdate();
	//描画終了。
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// ゲームの終了処理。
///////////////////////////////////////////////////////////////////
void TermnateGame()
{


}
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームエンジンの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	////タイトルシーンの作成。
	CSoundEngine sound;
	sound.Init();
	g_currentScene = new Title;
	g_fade = new Fade;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//サウンドの更新
		sound.Update();
		//ゲームの更新。
		UpdateGame();
	
		//ゲームの描画処理.
		RenderGame();

		
	}
	//ゲームの終了処理
	TermnateGame();
}