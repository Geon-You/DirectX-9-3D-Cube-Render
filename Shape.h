#pragma once
#include "Include.h"

class Shape
{
public:
	int shapeNum; // �ش� �ʵ尪���� � �޽ø� �׸� ������ ����
	D3DXVECTOR3 pos; // ��ġ
	D3DXVECTOR3 angle; // ȸ��
	D3DXVECTOR3 scale; // ũ��

	// �޽��� ���� �ʵ�
	LPD3DXMESH box; // 1
	LPD3DXMESH sphere; // 2
	LPD3DXMESH cylinder; // 3
	LPD3DXMESH teapot; // 4

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
};

