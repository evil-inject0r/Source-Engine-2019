#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#ifdef _WIN32
#pragma once
#endif

#include <Windows.h>
#include <DirectXMath.h>

#include <tier1/utlvector.h>


using namespace DirectX;

class MatrixStack : public IUnknown
{
public:
	CUtlVector<XMMATRIX>	m_stack;
	int						m_stackTop;

	HRESULT	Create(void);

	XMMATRIX* GetTop();
	void Push();
	void Pop();
	void LoadIdentity();
	void LoadMatrix(const XMMATRIX* pMat);
	void MultMatrix(const XMMATRIX* pMat);
	void MultMatrixLocal(const XMMATRIX* pMat);
	HRESULT ScaleLocal(FLOAT x, FLOAT y, FLOAT z);

	
	HRESULT RotateAxisLocal(const XMFLOAT3* pV, FLOAT Angle);

	HRESULT TranslateLocal(FLOAT x, FLOAT y, FLOAT z);
};

#endif //
