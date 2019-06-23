#ifndef DXABSTRACT_H
#define DXABSTRACT_H

#include "MatrixStack.h"

HRESULT	MatrixStack::Create()
{
	m_stack.EnsureCapacity(16);
	m_stack.AddToTail();
	m_stackTop = 0;

	LoadIdentity();

	return S_OK;
}

XMMATRIX* MatrixStack::GetTop()
{
	return (XMMATRIX*) &m_stack[m_stackTop];
}


void MatrixStack::Push()
{
}

void MatrixStack::Pop()
{
}

void MatrixStack::LoadIdentity()
{
}

void MatrixStack::LoadMatrix(const XMMATRIX* pMat)
{
}
void MatrixStack::MultMatrix(const XMMATRIX* pMat)
{
}

void MatrixStack::MultMatrixLocal(const XMMATRIX* pMat)
{
}

HRESULT MatrixStack::ScaleLocal(FLOAT x, FLOAT y, FLOAT z)
{
	return S_OK;
}

HRESULT MatrixStack::RotateAxisLocal(CONST XMFLOAT3* pV, FLOAT Angle)
{
	return S_OK;
}

HRESULT MatrixStack::TranslateLocal(FLOAT x, FLOAT y, FLOAT z)
{
	return S_OK;
}

#endif //