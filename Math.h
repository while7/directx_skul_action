#pragma once
#include "singleton.h"
class Math :
	public singleton<Math>
{
public:
	Math();
	virtual ~Math();

	template <typename T>
	void Lerp(T* target, T& start, T& finsh, float time)
	{
		*target = start + (finsh - start) * time * D_TIME;
	}

	Vector2 Rotate(Vector2 v, float rot);
	Vector2 Rotate(Object* obj, float rot);

	float Direction(Vector2 v1, Vector2 v2);
	float Direction(Object* obj1, Object* obj2);

	double Distance(Vector2 v1, Vector2 v2);
	double Distance(Object* obj1, Object* obj2);

	void Bazier(Vector2* target, Vector2& start,Vector2& control ,Vector2& finsh);

};

#define MATH Math::GetInstance()