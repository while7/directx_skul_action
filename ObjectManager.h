#pragma once
#include "singleton.h"
#include "Object.h"
class ObjectManager :
	public singleton<ObjectManager>
{
	friend class Object;
public:
	ObjectManager();
	virtual ~ObjectManager();

	list<Object*> ObjList[Tag::END_TAG];
	list<Collider*> ColliderList = {};

	bool collisionTag[END_TAG + 1][END_TAG + 1];

	Object* AddObject(const string& _Key, Object* _obj, Vector2 m_Pos, Tag _objTag)
	{
		_obj->Init();
		_obj->m_Tag = _objTag;
		_obj->vPos = m_Pos;
		_obj->m_Key = _Key;
		ObjList[_objTag].emplace_back(_obj);
		return _obj;
	}

	Object* FindObject(const string& _Key)
	{
		for (auto iter1 = 0; iter1 != Tag::END_TAG; iter1++)
			for (auto& iter2 : ObjList[iter1])
			{
				if (iter2->m_Key == _Key)
				{
					return iter2;
				}
			}
		return nullptr;
	}

	void AddCollsion(Collider* _collider) { ColliderList.emplace_back(_collider); }

	void Update();
	void Render();
	void Release();
	void CollisionCheck(Collider* collider);


	int IsMapOut(Object* obj)
	{
		if (obj->m_Tag == UI || obj->m_Tag == MOUSE)
		{
			return false;
		}
		else {
			return (obj->vPos.x < CAMERA->m_vCameraPos.x - center_vec2.x
				|| obj->vPos.x  > CAMERA->m_vCameraPos.x + center_vec2.x
				|| obj->vPos.y < CAMERA->m_vCameraPos.y - center_vec2.y
				|| obj->vPos.y  > CAMERA->m_vCameraPos.y + center_vec2.y);
		}
	}
	void ClearAllObjects();


};


#define OBJECT ObjectManager::GetInstance()