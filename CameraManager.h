#pragma once
#include "singleton.h"
class CameraManager :
	public singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

	D3DXMATRIX m_matProj, m_matView;

	Vector2 m_vCameraPos;
	Vector2 m_vViewSize;

	Vector3 m_vScale;
	Vector3 m_vEndScale;
	Vector3 m_vTarget;

	float m_fAngle;
	float m_ShakeTime;

	bool moveAlarm = false;

	void Init();
	void Release();

	void SetTransform();

	void MoveCamera(const Vector2& vPlusPos);

	void SetCamera(const Vector2& vSetPos);

	Vector2 WorldToView(Vector2 vec2)
	{
		vec2 = Vector2(vec2.x + GetMat()._41 + center_vec2.x, vec2.y - GetMat()._42 + center_vec2.y);
		return vec2;
	}
	Vector2 ViewToWorld(Vector2 vec2)
	{
		vec2 = Vector2(vec2.x - GetMat()._41 - center_vec2.x, vec2.y + GetMat()._42 - center_vec2.y);
		return vec2;
	}

	D3DXMATRIX GetMat()
	{
		D3DXMatrixInverse(&m_matView, NULL, &m_matView);
		return m_matView;
	}

	void Update();
	void Reset();

	void CameraShake(float _time);

};

#define CAMERA CameraManager::GetInstance()

