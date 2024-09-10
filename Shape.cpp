#include "Shape.h"
#include "Device.h"

void Shape::Initialize()
{
	auto device = GET_SINGLE(Device)->GetDevice();

	// 다이렉트에서 기본적으로 제공해주는 생성 함수(기본적으로 제공되는 모델에 대해서만)
	D3DXCreateBox(device, 2.f, 2.f, 2.f, &box, NULL);
	D3DXCreateSphere(device, 2.f, 20, 10, &sphere, NULL);
	D3DXCreateCylinder(device, 1.f, 1.f, 4.f, 10, 10, &cylinder, NULL);
	D3DXCreateTeapot(device, &teapot, NULL);

	shapeNum = 1;
	pos = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(1.f, 1.f, 1.f);
	angle = D3DXVECTOR3(0, 0, 0);
}

void Shape::Update()
{
	// 그릴 메시 설정
	if (GetAsyncKeyState('1')) shapeNum = 1;
	if (GetAsyncKeyState('2')) shapeNum = 2;
	if (GetAsyncKeyState('3')) shapeNum = 3;
	if (GetAsyncKeyState('4')) shapeNum = 4;

	// x축 회전
	if (GetAsyncKeyState('Q')) angle.x -= 1.f;
	if (GetAsyncKeyState('W')) angle.x += 1.f;

	// y축 회전
	if (GetAsyncKeyState('E')) angle.y -= 1.f;
	if (GetAsyncKeyState('R')) angle.y += 1.f;

	// z축 회전
	if (GetAsyncKeyState('T')) angle.z -= 1.f;
	if (GetAsyncKeyState('Y')) angle.z += 1.f;

	// 이동
	if (GetAsyncKeyState(VK_NUMPAD4)) pos.x -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD6)) pos.x += 1.f;

	if (GetAsyncKeyState(VK_NUMPAD8)) pos.y -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD2)) pos.y += 1.f;

	if (GetAsyncKeyState(VK_NUMPAD7)) pos.z -= 1.f;
	if (GetAsyncKeyState(VK_NUMPAD9)) pos.z += 1.f;
}

void Shape::Render()
{
	auto device = GET_SINGLE(Device)->GetDevice();

	// 광원 설정 (기본으로 광원이 켜져있음) -> 광원을 끌 거임
	// -> 광원 옵션은 켜져있지만, 실제 월드에 배치된 광원이 없으므로 광원을 끌 예정
	// 광원을 끌 경우, 메시의 버텍스가 가지고 있는 기본 색상이 나옴
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 그리기 상태 설정
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX matTrans; // 위치 행렬
	D3DXMATRIX matRot;	 // 회전 행렬
	D3DXMATRIX matScale; // 크기 행렬
	D3DXMATRIX matWorld; // 월드 행렬

	// 행렬 연산으로 여러 축의 회전을 표현 시,
	// 짐벌락 문제가 발생함
	// 이 짐벌락 문제를 해결 할 수 있는 것이 쿼터니언
	// 그리고 여러 축에 대한 회전 연산에 대해서는 쿼터니언이 연산속도가 더 빠름 (단일 축에 대한 계산은 행렬 연산이 더 빠름)
	// 행렬연산은 degree나 radian을 이용한 연산(직관적)을 하지만 쿼터니언은 우리가 직관적으로 알아볼 수 있는 연산이 아니다(수학적인 지식이 필요함).

	D3DXQUATERNION q; // 쿼터니언
	D3DXVECTOR3 radAngle; // 라디안으로 변환한 앵글 값을 가질 벡터

	radAngle.x = D3DXToRadian(angle.x);
	radAngle.y = D3DXToRadian(angle.y);
	radAngle.z = D3DXToRadian(angle.z);

	// 위치 행렬 변환
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);

	// 회전 행렬 변환
	D3DXQuaternionRotationYawPitchRoll(&q, radAngle.y, radAngle.x, radAngle.z);
	D3DXMatrixRotationQuaternion(&matRot, &q);

	// 크기 행렬 변환
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	// 월드 행렬 연산
	matWorld = matScale * matRot * matTrans;
	// 연산한 월드 행렬을 적용
	device->SetTransform(D3DTS_WORLD, &matWorld);

	// shapeNum 값에 따라 특정 메시 그리기
	switch (shapeNum)
	{
	case 1: box->DrawSubset(0); break; // 계층 구조에서 하위 메시까지 전부 그려짐
	case 2: sphere->DrawSubset(0); break; // 계층 구조에서 하위 메시까지 전부 그려짐
	case 3: cylinder->DrawSubset(0); break; // 계층 구조에서 하위 메시까지 전부 그려짐
	case 4: teapot->DrawSubset(0); break; // 계층 구조에서 하위 메시까지 전부 그려짐
	}
}

void Shape::Release()
{
	if (box)
	{
		box->Release(); // 다이렉트에서 기본적으로 제공하는 Release() 함수
		delete box;
		box = nullptr;
	}

	if (sphere)
	{
		sphere->Release(); // 다이렉트에서 기본적으로 제공하는 Release() 함수
		delete sphere;
		sphere = nullptr;
	}

	if (cylinder)
	{
		cylinder->Release(); // 다이렉트에서 기본적으로 제공하는 Release() 함수
		delete cylinder;
		cylinder = nullptr;
	}

	if (teapot)
	{
		teapot->Release(); // 다이렉트에서 기본적으로 제공하는 Release() 함수
		delete teapot;
		teapot = nullptr;
	}
}
