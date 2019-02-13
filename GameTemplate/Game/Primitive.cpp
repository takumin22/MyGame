#include "stdafx.h"
#include "Primitive.h"



CPrimitive::CPrimitive()
{
}
CPrimitive::~CPrimitive()
{
	Release();
}
void CPrimitive::Release()
{
	m_vertexBuffer.Release();
	m_indexBuffer.Release();
}
bool CPrimitive::Create(
	D3D_PRIMITIVE_TOPOLOGY topology,
	int numVertex,
	int vertexStride,
	void* pSrcVertexBuffer,
	int numIndex,
	CIndexBuffer::EnIndexType indexType,
	void* pSrcIndexBuffer)
{
	Release();
	bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
	return true;
}
void CPrimitive::Draw(CRenderContext& rc)
{
	//���_�o�b�t�@��ݒ�B
	rc.IASetVertexBuffer(m_vertexBuffer);
	rc.IASetIndexBuffer(m_indexBuffer);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	rc.IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�`��B
	rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
}