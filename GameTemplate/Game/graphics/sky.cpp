#include "stdafx.h"
#include "sky.h"


sky::sky()
{
}


sky::~sky()
{
	Relese();
}
void sky::Relese()
{
	if (m_srv != nullptr) {
		m_srv->Release();
		m_srv = nullptr;
	}
	m_isValid = false;
}
void sky::Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale)
{
	m_scale = scale;
	m_skinmodel.Init(modelfilePath);
	CreateFromDDSTextureFromFile(mapfilepath);
	m_skinmodel.FindMesh([&](auto& mat)
	{
		ModelEffect* effect = reinterpret_cast<ModelEffect*>(mat->effect.get());
		effect->SetAlbedoTexture(m_srv);
	});

}
bool sky::CreateFromDDSTextureFromFile(const wchar_t* fileName)
{
	Relese();
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), fileName, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &m_srv);
	if (FAILED(hr))
	{
		throw;
		return false;
	}
	return true;
}
void sky::Update()
{

	m_skinmodel.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
}

void sky::Draw()
{
	m_skinmodel.Draw(
		enRenderMode_CubeMap,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}