#include "Ingame.h"
#include "Include.h"
#include "Device.h"

void Ingame::Initialize()
{
	// 이전(2D에서)까지 사용했던 변환
	// 로컬(모델) 스페이스 -> 월드 변환

	// 이번에 추가적으로 진행할 변환 (3D 공간을 2D에 나타내기 위한 변환)
	// 뷰 변환 -> 프로젝션 변환
	// 뷰 변환을 통해 월드 상에 카메라를 정의하고,
	// 프로젝션 변환을 통해 카메라가 어떤 식으로 월드를 렌더할 것인지를 결정 (직교 - Orthographic, 원근 - Perspective)

	// 뷰 변환을 위해 뷰 행렬을 정의
	// 카메라의 위치를 나타내는 벡터 -> eye
	// 카메라가 바라보고 있는 방향을 나타내는 벡터 -> lookAt
	// 월드 상에서 양의 y축(위쪽)을 가리키는 크기가 1인 벡터 -> up
	// 위의 3개의 벡터를 통해 뷰 행렬을 구성함

	// up 벡터의 설명 보충
	// up 벡터를 통해 카메라의 기저 축을 만드는 작업을 함

	// 뷰 행렬 4x4
	// right.x,   right.y,   right.z,   0		<- 카메라의 기저 x축
	// up.x,	  up.y,	     up.z,	    0		<- 카메라의 기저 y축
	// forward.x, forward.y, forward.z, 0		<- 카메라의 기저 z축
	// eye.x,	  eye.y,	 eye.z,		1		<- 카메라의 위치

	// 게임에서 일반적으로 많이 사용되는 투영 방식은 2가지
	// Orthographic		<- 원근법 적용 X
	// Perspective		<- 원근법 적용 O

	// Perspective 기준으로 투영 행렬로 인해 모델들의 크기가 거리에 따라 다르게 보임
	// 1. 종횡비 (Aspect ratio) -> 장치마다 다른 종횡비에 따라 x, y 값을 조정 (일반적으론 수직 fov를 사용하고 그때의 aspective ratio = width / height)
	// 2. 시야각 (FOV : Field Of View) 설정 -> 시야각에 의해 객체를 더 적게 또는 더 많이 보게 됨
	//										  시야각에 의해서도 x, y 값을 조정
	// 3. 정규화 : x(-1 ~ 1), y(-1 ~ 1), z(-1 ~ 1) 좌표들을 정규화시켜, NDC(정규화된 장치 공간, 카메라에 의해 그려지는 육면체 프러스텀 공간)를 얻음

	// 뷰포트 (viewport)
	// 장치에 의존적인 좌표 체계로 변환
	// 기본적으로 클라이언트 해상도로 설정

	// 카메라의 위치
	eye = D3DXVECTOR3(0, 0, -10.f);

	// 카메라가 보는 지점
	lookAt = D3DXVECTOR3(0, 0, 0);

	// 카메라의 상향 벡터
	up = D3DXVECTOR3(0, 1, 0);

	// 외적을 통해 카메라의 기저 벡터를 만들어 냄
	// 뷰 행렬 연산 (왼손좌표계 기준)
	D3DXMatrixLookAtLH(&view, &eye, &lookAt, &up);
	// 연산한 뷰 행렬을 적용
	auto device = GET_SINGLE(Device)->GetDevice();
	device->SetTransform(D3DTS_VIEW, &view);

	// 투영 행렬
	D3DXMatrixPerspectiveFovLH(&projection, D3DX_PI * .5f, 1, 1, 100);
	// 연산한 투영 행렬을 장치에 적용
	device->SetTransform(D3DTS_PROJECTION, &projection);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	// 클라이언트 해상도를 기반으로 한 뷰포트 생성
	D3DVIEWPORT9 vp = { 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0, 1 };
	// 생성한 뷰포트 적용
	device->SetViewport(&vp);

	shape.Initialize();
	shape.shapeNum = 1;
}

int Ingame::Update()
{
	shape.Update();

	return 0;
}

void Ingame::Render()
{
	shape.Render();
}

void Ingame::Release()
{
	shape.Release();
}

Ingame::Ingame()
{
}

Ingame::~Ingame()
{
    Release();
}
