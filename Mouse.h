#pragma once
#include "Object.h"
class Mouse :
	public Object
{
public:
	Mouse();
	virtual ~Mouse();
	float dir = 0;
	// Object��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void onCollisionStay(Collider* col) override;
	virtual void onCollisionExit(Collider* col) override;
};

