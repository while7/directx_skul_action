#include "DXUT.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::Jump(Vector2 vec2)
{
	vPos += vec2 * speed * D_TIME;
}

void Object::KnockBack(Object* give, float force)
{
	vPos.x += give->scale * force * D_TIME;
}

Object* Object::NearObject(Tag tag)
{
	float short_distance = 10000000;
	float temp_distance;
	Object* near_obj = this;

	for (Object* iter : OBJECT->ObjList[tag])
	{
		if (iter == this)
			continue;
		temp_distance = MATH->Distance(this, iter);
		if (short_distance > temp_distance)
		{
			short_distance = temp_distance;
			near_obj = iter;
		}
	}

	return near_obj;
}

int Object::AdjustYAxis(Object* target, int range)
{
	if (target == nullptr)
		return 0;
	if (vPos.y > target->vPos.y - range && vPos.y < target->vPos.y + range)
	{
		return 0; //0 µü¸ÂÀ½
	}
	else if (vPos.y < target->vPos.y - range)
	{
		return 1;
	}
	else if (vPos.y > target->vPos.y + range)
	{
		return -1;
	}
	return 0;
}

int Object::AdjustXAxis(Object* target, int range)
{
	if (target == nullptr)
		return 0;
	if (vPos.x <= target->vPos.x && vPos.x + range >= target->vPos.x)
	{
		scale = 1;
		return 0;
	}
	if (vPos.x - range <= target->vPos.x && vPos.x >= target->vPos.x)
	{
		scale = -1;
		return 0;
	}
	if (target->scale == 1)
	{
		if (target->vPos.x <= vPos.x)
		{
			scale = -1;
			return -1;
		}
		else
		{
			scale = 1;
			return 1;
		}
	}
	else if (target->scale == -1)
	{
		if (target->vPos.x >= vPos.x)
		{
			scale = 1;
			return 1;
		}
		else
		{
			scale = -1;
			return -1;
		}
	}
	return 0;
}