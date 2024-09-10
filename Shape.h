#pragma once
#include "Include.h"

class Shape
{
public:
	int shapeNum; // 해당 필드값으로 어떤 메시를 그릴 것인지 결정
	D3DXVECTOR3 pos; // 위치
	D3DXVECTOR3 angle; // 회전
	D3DXVECTOR3 scale; // 크기

	// 메쉬를 담을 필드
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

