#pragma once
#include "RenderTarget.h"
#include "../Sprite.h"
/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};

class RenderTarget;


/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	void ChangeBackBaffer() {
		//���ɖ߂��B
		m_pd3dDeviceContext->OMSetRenderTargets(
			1,
			&oldRenderTargetView,
			oldDepthStencilView
		);
		m_pd3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
		//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
		oldRenderTargetView->Release();
		oldDepthStencilView->Release();

	}
	/// <summary>
	/// �Q�[���Ńf�t�H���g�̃t�H���g���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�f�[�^�iDirectX::SpriteFont*�j
	/// </returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_SpriteFont;
	}
	/// <summary>
	/// �t�H���g�\���ɕK�v�ȃN���X���擾
	/// </summary>
	/// <returns>
	/// �t�H���g�\���ɕK�v�ȃN���X�iDirectX::SpriteBatch*�j
	/// </returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_SpriteBatch;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);
	void OldView();
	/// <summary>
	/// ���X�^���C�U�X�e�[�g�̃Q�b�g
	/// </summary>
	/// <returns>
	/// ���X�^���C�U�X�e�[�g�iID3D11RasterizerState* �j
	/// </returns>
	ID3D11RasterizerState* GetRasterizerState()
	{
		return m_rasterizerState;
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	DirectX::SpriteFont*    m_SpriteFont = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�f�[�^
	DirectX::SpriteBatch*   m_SpriteBatch = NULL;		//�Q�[���̃f�t�H���g�̃t�H���g�\���p�f�[�^
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	RenderTarget m_mainRenderTarget;
};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��