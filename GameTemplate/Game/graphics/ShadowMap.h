#pragma once
#include "RenderTarget.h"

class SkinModel;
/// <summary>
/// シャドウマップクラス。
/// </summary>
/// <code>
/// //シャドウマップを生成するサンプルコード。
/// int main()
/// {
///		ShadowMap g_shadowMap;
///		C3DModelDraw playerModel;
///		C3DModelDraw bgModel;
///			・
///			省略
///			・
///		//ゲームループ。
///		while( true )
///		{
///				・
///				省略
///				・
///			//シャドウキャスターを登録。
///			g_shadowMap.RegistShadowCaster(&playerModel);
///			g_shadowMap.Update();
///				・
///				省略
///				・
///			//シャドウマップを作成、
///			g_shadowMap.RenderToShadowMap();
///				・
///				省略
///				・
///		}
/// }
/// </code>
class ShadowMap
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	ShadowMap();
	/// <summary>
	/// デストラクタ。
	/// </summary>
	~ShadowMap();
	/// <summary>
	/// ライトビュー行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLighViewMatrix()
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ライトプロジェクション行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix()
	{
		return m_lightProjMatrix;
	}
	/// <summary>
	/// 更新。
	/// </summary>
	/// <remarks>
	/// ライトビュー行列や、ライトプロジェクション行列を
	/// 更新します。毎フレーム呼び出してください。
	/// </remarks>
	/// <param name="pos">ライトカメラの視点の座標</param>
	/// <param name="target">ライトかめらの注視点の座標</param>
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	/// <summary>
	/// シャドウマップにシャドウキャスターをレンダリング。
	/// 毎フレーム呼び出して下さい。
	/// </summary>
	/// <remarks>
	/// シャドウマップに描画されるシャドウキャスターは
	/// RegistShadowCaster関数を使用して登録されたキャスターのみです。
	/// この関数を呼び出すと、シャドウキャスターのリストはクリアされます。
	/// </remarks>
	void RenderToShadowMap();
	/// <summary>
	/// シャドウキャスターを登録。
	/// </summary>
	/// <remarks>
	/// この関数を使って、登録されたキャスターが
	/// シャドウマップに描画されます。
	/// 登録されたキャスターのリストはRenderToShadowMapを呼び出したら
	/// クリアされるため、常に影を生成したい場合は、
	/// 毎フレームこの関数を呼び出す必要があります。
	/// </remarks>
	/// <param name="shadowCaster">シャドウキャスター</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	/// <summary>
	/// シャドウキャスターをリストから除外する。
	/// </summary>
	/// <param name="shadowCaster"></param>
	void UnregistShadowCaster(SkinModel* shadowCaster)
	{
		//shadowCasterのインスタンスをリストから検索する。
		auto it = std::find(
			m_shadowCasters.begin(),
			m_shadowCasters.end(),
			shadowCaster
		);
		if (it != m_shadowCasters.end()) {
			//見つかったのでコンテナから除外する。
			m_shadowCasters.erase(it);
		}
	}
	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns>シャドウマップのSRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;						//シャドウマップを描画するレンダリングターゲット。
	std::vector< SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。

};

extern ShadowMap* g_shadowMap;		//!<シャドウマップ