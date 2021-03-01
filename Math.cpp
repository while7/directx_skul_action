#include "DXUT.h"
#include "Math.h"


Math::Math()
{
}


Math::~Math()
{
}

Vector2 Math::Rotate(Vector2 v, float rot)
{
	float _rot = D3DXToDegree(rot);
	return Vector2(v.x * cos(_rot) + v.y * -sin(_rot), v.x * sin(_rot) + v.y * cos(rot));
}

Vector2 Math::Rotate(Object* obj, float rot)
{
	return Rotate(obj->vPos, rot);
}

float Math::Direction(Vector2 v1, Vector2 v2)
{
	return D3DXToDegree(atan2f(v2.y - v1.y, v2.x - v1.x));
}

float Math::Direction(Object* obj1, Object* obj2)
{
	return Direction(obj1->vPos, obj2->vPos);
}

double Math::Distance(Vector2 v1, Vector2 v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}

double Math::Distance(Object* obj1, Object* obj2)
{
	if (obj2 != nullptr)
		return Distance(obj1->vPos, obj2->vPos);
}

void Math::Bazier(Vector2 * target, Vector2 & start,Vector2& control ,Vector2 & finsh)
{
	Vector2 v1, v2, v3;
	v1 = start;
	v2 = control;
	Lerp<Vector2>(&v1, v1, v2, 1);
	Lerp<Vector2>(&v2, v2, finsh, 1);
	Lerp<Vector2>(&v3, v1, v2,1);
}
