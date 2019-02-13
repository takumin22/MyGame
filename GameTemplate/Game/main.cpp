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
	//現在のシーンの更新。
	g_currentScene->Update();
	//g_shadowMap->RegistShadowCaster(&);
	//シャドウマップを更新。
	//g_shadowMap->Update(
	//	{ 0.0f, 1000.0f, 0.0f },
	//	{0.0f,0.0f,0.0f}
	//);*/
}
///////////////////////////////////////////////////////////////////
// ゲームの描画処理。
///////////////////////////////////////////////////////////////////
void RenderGame()
{
	
	

	//描画開始。
	g_graphicsEngine->BegineRender();
    
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;

	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);


	//シャドウマップにレンダリング
	g_shadowMap->RenderToShadowMap();

	//元に戻す。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();


	//現在のシーンの描画。
	g_currentScene->Draw();

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
	g_currentScene = new Title;


	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//ゲームの更新。
		UpdateGame();
		//ゲームの描画処理。
		RenderGame();
		
	}
	//ゲームの終了処理
	TermnateGame();
}