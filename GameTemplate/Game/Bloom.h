#pragma once
#include "graphics/RenderTarget.h"
#include "graphics/Shader.h"

class PostEffect;

/// <summary>
/// �u���[��
/// </summary>
class Bloom
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bloom();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bloom();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(PostEffect& postEffect);
private:
	/// <summary>
	/// �A���t�@�u�����f�B���O�̃X�e�[�g������������B
	/// </summary>
	void InitAlphaBlendState();
	/// <summary>
	/// �萔�o�b�t�@�̏������B
	/// </summary>
	void InitConstantBuffer();
	/// <summary>
	/// �V�F�[�_�[���������B
	/// </summary>
	void InitShader();
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̏������B
	/// </summary>
	void InitRenderTarget();
	/// <summary>
	/// �T���v���X�e�[�g�̏������B
	/// </summary>
	void InitSamplerState();
private:
	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
										/*!
										* @brief	�u���[�p�̃p�����[�^�o�b�t�@�B
										*@details
										* �����ύX������AAssets/shader/bloom.fx��CBBlur�̒��g���ύX����悤�ɁB
										*/
	struct SBlurParam {
		CVector4 offset;
		float weights[NUM_WEIGHTS];
	};
	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	RenderTarget m_luminanceRT;			//�P�x�𒊏o���郌���_�����O�^�[�Q�b�g
	RenderTarget m_downSamplingRT[2];	//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
	Shader m_vs;						//�������Ȃ����_�V�F�[�_�[�B
	Shader m_psLuminance;				//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
	Shader m_vsXBlur;					//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;					//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;					//�u���[�p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psFinal;					//�ŏI�����p�̃s�N�Z���V�F�[�_�[�B

	SBlurParam m_blurParam;				//�u���[�p�̃p�����[�^�B
	float m_blurDispersion = 50.0f;		//�u���[�̕��U��B�傫������قǋ������U����B
	ID3D11Buffer* m_blurParamCB = nullptr;	//�u���[�p�����[�^�p�̒萔�o�b�t�@�B
};

