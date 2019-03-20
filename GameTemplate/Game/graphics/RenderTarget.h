#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	// レンダリングターゲットの作成。 
	void Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat);
	/// <summary>
	/// レンダリングターゲットの解放。
	/// </summary>
	void Release();
	// レンダリングターゲットとデプスステンシルのクリア。 
	void ClearRenderTarget(float* clearColor);
	// レンダリングターゲットビューを取得。 
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}
	// デプスステンシルビューを取得。 
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}
	// レンダリングターゲットのSRVを取得。 
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	/// <summary>
	/// ビューポートの取得。
	/// </summary>
	/// <returns>ビューポート</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
	/// <summary>
	/// レンダリングターゲットの幅を取得。
	/// </summary>
	/// <returns></returns>
	float GetWidth() const
	{
		return m_width;
	}
	/// <summary>
	/// レンダリングターゲットの高さを取得。
	/// </summary>
	/// <returns></returns>
	float GetHeight() const
	{
		return m_height;
	}
	/// <summary>
	/// レンダリングターゲットとなっているテクスチャのフォーマットを取得。
	/// </summary>
	/// <returns></returns>
	DXGI_FORMAT GetTextureFormat() const
	{
		return m_format;
	}
private:
	float m_width = 0;										//!<レンダリングターゲットの幅。
	float m_height = 0;										//!<レンダリングターゲットの高さ。
	//ここからレンダリングターゲット関係のメンバ変数です。
	DXGI_FORMAT m_format = DXGI_FORMAT_UNKNOWN;				//レンダリングターゲットのフォーマット。
	ID3D11Texture2D * m_renderTargetTex = nullptr;		//!<レンダリングターゲットとなるテクスチャ。
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<レンダーターゲットビュー。
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<レンダリングターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<デプスステンシルとなるテクスチャ。
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<デプスステンシルビュー。
	D3D11_VIEWPORT				m_viewport;
};

