#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "graphics/ShadowMap.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	switch (m_renderMode) {
	case enRenderMode_Normal: {
		//通常描画。
		//シェーダーを適用する。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(3, 1, &m_albedoTex);
		//todo シェーダーリソースビューを一気に設定する。
		ID3D11ShaderResourceView* srvArray[] = {
			g_shadowMap->GetShadowMapSRV()	//シャドウマップ。
		};
		deviceContext->PSSetShaderResources(4,1,srvArray);
	}
		break;
	case enRenderMode_CreateShadowMap:
		//todo シャドウマップ生成用のシェーダーを設定。
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}

}