#include "stdafx.h"
#include "sky.h"

//todo ��}�b�v�B
ID3D11ShaderResourceView* g_skyMapSRV = nullptr;
sky::sky()
{
	m_skinmodel.Init(L"Assets/modelData/sky.cmo");

	//todo ��}�b�v�����[�h�B
	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Resource/sprite/skyCubeMap.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_skyMapSRV);
	m_skinmodel.SetskyMap(g_skyMapSRV);

}


sky::~sky()
{
}
void sky::Update()
{

	m_skinmodel.UpdateWorldMatrix(m_position, CQuaternion::Identity(), CVector3{10000.0f, 10000.0f, 10000.0f});
}

void sky::Draw()
{
	m_skinmodel.Draw(
		enRenderMode_CubeMap,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}