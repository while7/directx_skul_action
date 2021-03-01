#pragma once
#include "Object.h"

class Object;

class Collider :
	public RECT
{
public:
	Collider();
	Collider(Tag tag);
	~Collider();

	Collider* collision;
	RECT overlap_rect;

	Object* lpGameObject = nullptr;

	Tag m_tag;

	Vector2 m_pos;

	float damage;
	bool isEnable;

	void Enable()
	{
		isEnable = true;
	}
	void UnEnable()
	{
		isEnable = false;
	}
	void SetTag(Tag tag)
	{
		m_tag = tag;
	}

	void Draw(char r, char g, char b);

	void SetRange(Vector2 Pos,float width, float height);

	static void ColliderInit(Object* owner, Collider** col, ObjectTag tag, float damage, bool isEnable);

	RECT GetRect()
	{
		RECT rt;

		rt.left = left;
		rt.right = right;
		rt.top = top;
		rt.bottom = bottom;
		return rt;
	}
};

