#include "Shape.h"
#include "Device.h"

void Shape::Initialize()
{
	auto device = GET_SINGLE(Device)->GetDevice();

	// ���̷�Ʈ���� �⺻������ �������ִ� ���� �Լ�(�⺻������ �����Ǵ� �𵨿� ���ؼ���)
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
	// �׸� �޽� ����
	if (GetAsyncKeyState('1')) shapeNum = 1;
	if (GetAsyncKeyState('2')) shapeNum = 2;
	if (GetAsyncKeyState('3')) shapeNum = 3;
	if (GetAsyncKeyState('4')) shapeNum = 4;

	// x�� ȸ��
	if (GetAsyncKeyState('Q')) angle.x -= 1.f;
	if (GetAsyncKeyState('W')) angle.x += 1.f;

	// y�� ȸ��
	if (GetAsyncKeyState('E')) angle.y -= 1.f;
	if (GetAsyncKeyState('R')) angle.y += 1.f;

	// z�� ȸ��
	if (GetAsyncKeyState('T')) angle.z -= 1.f;
	if (GetAsyncKeyState('Y')) angle.z += 1.f;

	// �̵�
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

	// ���� ���� (�⺻���� ������ ��������) -> ������ �� ����
	// -> ���� �ɼ��� ����������, ���� ���忡 ��ġ�� ������ �����Ƿ� ������ �� ����
	// ������ �� ���, �޽��� ���ؽ��� ������ �ִ� �⺻ ������ ����
	device->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �׸��� ���� ����
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX matTrans; // ��ġ ���
	D3DXMATRIX matRot;	 // ȸ�� ���
	D3DXMATRIX matScale; // ũ�� ���
	D3DXMATRIX matWorld; // ���� ���

	// ��� �������� ���� ���� ȸ���� ǥ�� ��,
	// ������ ������ �߻���
	// �� ������ ������ �ذ� �� �� �ִ� ���� ���ʹϾ�
	// �׸��� ���� �࿡ ���� ȸ�� ���꿡 ���ؼ��� ���ʹϾ��� ����ӵ��� �� ���� (���� �࿡ ���� ����� ��� ������ �� ����)
	// ��Ŀ����� degree�� radian�� �̿��� ����(������)�� ������ ���ʹϾ��� �츮�� ���������� �˾ƺ� �� �ִ� ������ �ƴϴ�(�������� ������ �ʿ���).

	D3DXQUATERNION q; // ���ʹϾ�
	D3DXVECTOR3 radAngle; // �������� ��ȯ�� �ޱ� ���� ���� ����

	radAngle.x = D3DXToRadian(angle.x);
	radAngle.y = D3DXToRadian(angle.y);
	radAngle.z = D3DXToRadian(angle.z);

	// ��ġ ��� ��ȯ
	D3DXMatrixTranslation(&matTrans, pos.x, pos.y, pos.z);

	// ȸ�� ��� ��ȯ
	D3DXQuaternionRotationYawPitchRoll(&q, radAngle.y, radAngle.x, radAngle.z);
	D3DXMatrixRotationQuaternion(&matRot, &q);

	// ũ�� ��� ��ȯ
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	// ���� ��� ����
	matWorld = matScale * matRot * matTrans;
	// ������ ���� ����� ����
	device->SetTransform(D3DTS_WORLD, &matWorld);

	// shapeNum ���� ���� Ư�� �޽� �׸���
	switch (shapeNum)
	{
	case 1: box->DrawSubset(0); break; // ���� �������� ���� �޽ñ��� ���� �׷���
	case 2: sphere->DrawSubset(0); break; // ���� �������� ���� �޽ñ��� ���� �׷���
	case 3: cylinder->DrawSubset(0); break; // ���� �������� ���� �޽ñ��� ���� �׷���
	case 4: teapot->DrawSubset(0); break; // ���� �������� ���� �޽ñ��� ���� �׷���
	}
}

void Shape::Release()
{
	if (box)
	{
		box->Release(); // ���̷�Ʈ���� �⺻������ �����ϴ� Release() �Լ�
		delete box;
		box = nullptr;
	}

	if (sphere)
	{
		sphere->Release(); // ���̷�Ʈ���� �⺻������ �����ϴ� Release() �Լ�
		delete sphere;
		sphere = nullptr;
	}

	if (cylinder)
	{
		cylinder->Release(); // ���̷�Ʈ���� �⺻������ �����ϴ� Release() �Լ�
		delete cylinder;
		cylinder = nullptr;
	}

	if (teapot)
	{
		teapot->Release(); // ���̷�Ʈ���� �⺻������ �����ϴ� Release() �Լ�
		delete teapot;
		teapot = nullptr;
	}
}
