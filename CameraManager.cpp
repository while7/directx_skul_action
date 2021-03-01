#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
	Init();
}


CameraManager::~CameraManager()
{
	Release();
}

void CameraManager::Init()
{
	m_vCameraPos = center_vec2;
	m_vViewSize = Vector2((float)WINSIZEX, (float)WINSIZEY);
	m_vScale = m_vEndScale = Vector3(1, 1, 1);

	m_fAngle = 0.0f;
	m_ShakeTime = 0;

	D3DXMatrixOrthoLH(&m_matProj, m_vViewSize.x, -m_vViewSize.y, 0, 1);

}

void CameraManager::Release()
{
}

void CameraManager::SetTransform()
{
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &m_matView);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void CameraManager::MoveCamera(const Vector2 & vPlusPos)
{
	m_vCameraPos += vPlusPos;
}

void CameraManager::SetCamera(const Vector2 & vSetPos)
{
	m_vCameraPos = vSetPos;

}

void CameraManager::Update()
{
	if (m_ShakeTime >= timeGetTime())
	{
		m_vCameraPos += D3DXVECTOR2(rand() % 20 - 10, rand() % 20 - 10);
	}

	this->m_matView = D3DXMATRIX(
		m_vScale.x, 0, 0, 0,
		0, m_vScale.y, 0, 0,
		0, 0, m_vScale.z, 0,
		-m_vCameraPos.x, -m_vCameraPos.y, 0, 1);
}

void CameraManager::Reset()
{
	m_vCameraPos = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	m_vScale = m_vEndScale = D3DXVECTOR3(1, 1, 1);

	m_fAngle = 0.0f;
}

void CameraManager::CameraShake(float _time)
{
	if (m_ShakeTime <= _time + timeGetTime())
		m_ShakeTime = _time + timeGetTime();
}
