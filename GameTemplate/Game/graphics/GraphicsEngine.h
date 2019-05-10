#pragma once
#include "RenderTarget.h"
#include "../Sprite.h"
/// <summary>
/// レンダリングモード。
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};

class RenderTarget;


/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	void ChangeBackBaffer() {
		//元に戻す。
		m_pd3dDeviceContext->OMSetRenderTargets(
			1,
			&oldRenderTargetView,
			oldDepthStencilView
		);
		m_pd3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
		//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
		oldRenderTargetView->Release();
		oldDepthStencilView->Release();

	}
	/// <summary>
	/// ゲームでデフォルトのフォントを取得
	/// </summary>
	/// <returns>
	/// フォントデータ（DirectX::SpriteFont*）
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// フォント表示に必要なクラスを取得
	/// </summary>
	/// <returns>
	/// フォント表示に必要なクラス（DirectX::SpriteBatch*）
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	/// <summary>
	/// エフェクトのマネージャークラスの取得
	/// </summary>
	/// <returns>
	/// エフェクトのマネージャークラス（Effekseer::Manager*）
	/// </returns>
	Effekseer::Manager* GetEffekseerManager()
	{
		return m_effekseerManager;
	}
	void EffectUpdate()
	{
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		m_effekseerRenderer->SetCameraMatrix(efCameraMat);
		m_effekseerRenderer->SetProjectionMatrix(efProjMat);
		//Effekseerを更新。
		m_effekseerManager->Update();
		EffectDraw();
	}
	void EffectDraw()
	{
		//エフェクトは不透明オブジェクトを描画した後で描画する。
		m_effekseerRenderer->BeginRendering();
		m_effekseerManager->Draw();
		m_effekseerRenderer->EndRendering();
	}
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	void OldView();
	/// <summary>
	/// ラスタライザステートのゲット
	/// </summary>
	/// <returns>
	/// ラスタライザステート（ID3D11RasterizerState* ）
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//ゲームのデフォルトのフォントデータ
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//ゲームのデフォルトのフォント表示用データ
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	RenderTarget m_mainRenderTarget;
	Effekseer::Manager*	m_effekseerManager = nullptr;	//エフェクトマネージャークラス
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;  //エフェクトレンダラークラス
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン