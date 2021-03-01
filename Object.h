#pragma once
#include "Collider.h"

class Object
{
public:
	Object();
	virtual ~Object();

	Vector2 vPos = { 0,0 };
	Collider* col = nullptr;
	Collider* col2 = nullptr;
	Collider* col3 = nullptr;
	Collider* col4 = nullptr;
	Collider* col5 = nullptr;
	Tag m_Tag;
	string m_Key;
	texture* image = nullptr;

	bool isDestroy = false;
	bool isStun = false;
	bool invincibility = false;

	float damage; /* 데미지 계수 계산전 데미지, 실질적으로 사용하지는 않고 연산용 */
	float speed;
	int hp;
	int max_hp;
	float level;
	float exp;
	float gravity;
	bool isGravity;
	float scale, r, g, b, a;
	int add_damage = 0;
	int add_hp = 0;

	void Jump(Vector2 vec2);
	void KnockBack(Object* give, float force);
	Object* NearObject(Tag tag);
	int AdjustYAxis(Object* target, int range = 25);
	int AdjustXAxis(Object* target, int range = 25);

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void onCollisionStay(Collider* col) PURE;
	virtual void onCollisionExit(Collider* col) PURE;

	bool CheckDestroy() { return isDestroy; }
};

