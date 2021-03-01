#include "DXUT.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager()
	:collisionTag{
		{ 0,0,0,0,0,0,0,0,0,0 },//	NONE		1
		{ 0,0,0,0,1,0,0,0,0,0 },//	Player		2
		{ 0,0,0,1,0,0,0,0,0,0 },//	Enemy		3
		{ 0,0,0,0,0,0,0,0,0,0 },//	Attack		4
		{ 0,0,0,0,0,0,0,0,0,0 },//	EAttack		5
		{ 0,0,0,0,0,0,1,0,0,0 },//	UI			6
		{ 0,0,0,0,0,0,0,0,0,0 },//	MOUSE		7
		{ 0,0,0,0,0,0,0,0,0,0 },//	Boss		8
		{ 0,0,0,0,0,0,0,0,0,0 },//	Platform	9
		{ 0,0,0,0,0,0,0,0,0,0 },//	END,		10
	}
{
}


ObjectManager::~ObjectManager()
{
	for (int i = NONE_TAG + 1; i < END_TAG; i++)
	{
		for (auto iter = ObjList[i].begin(); iter != ObjList[i].end();)
		{
			if ((*iter) == nullptr)
				iter++;
			(*iter)->Release();
			SAFE_DELETE(*iter);
			iter++;
		}
	}
}

void ObjectManager::Update()
{
	for (int i = NONE_TAG; i < END_TAG; i++)
	{
		for (auto iter = ObjList[i].begin(); iter != ObjList[i].end();)
		{
			if ((*iter)->CheckDestroy())
			{
				ColliderList.remove((*iter)->col);
				ColliderList.remove((*iter)->col2);
				ColliderList.remove((*iter)->col3);
				ColliderList.remove((*iter)->col4);
				ColliderList.remove((*iter)->col5);
				(*iter)->Release();
				SAFE_DELETE(*iter);
				iter = ObjList[i].erase(iter);
			}
			else if (IsMapOut(*iter))
			{
				if ((*iter)->m_Tag == ENEMY)
				{
					iter++;
				}
				else
				{
					ColliderList.remove((*iter)->col);
					ColliderList.remove((*iter)->col2);
					ColliderList.remove((*iter)->col3);
					ColliderList.remove((*iter)->col4);
					ColliderList.remove((*iter)->col5);
					(*iter)->Release();
					SAFE_DELETE(*iter);
					iter = ObjList[i].erase(iter);
				}
			}
			else
			{
				(*iter)->Update();
				iter++;
			}
		}
	}
	for (auto& iter = ColliderList.begin(); iter != ColliderList.end(); iter++)
	{
		CollisionCheck((*iter));
	}
}

void ObjectManager::Render()
{
	for (int i = 0; i < END_TAG; i++)
	{
		for (auto iter : ObjList[i])
			iter->Render();
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < END_TAG; i++)
	{
		for (auto iter : ObjList[i])
			iter->Release();
	}
}

void ObjectManager::CollisionCheck(Collider * collider)
{
	for (auto& iter = ColliderList.begin(); iter != ColliderList.end();)
	{
		if ((*iter) == nullptr) { ColliderList.remove((*iter));  iter++; }
		if (!(collider->isEnable) || !((*iter)->isEnable)) { iter++; continue; }
		if (collisionTag[collider->m_tag][(*iter)->m_tag])
		{
			RECT rc2;
			if (IntersectRect(&rc2, &collider->GetRect(), &(*iter)->GetRect()))
			{
				collider->lpGameObject->onCollisionStay((*iter));
				collider->collision = (*iter);
				collider->overlap_rect = rc2;
			}
			else
			{
				collider->lpGameObject->onCollisionExit((*iter));
			}
		}
		iter++;
	}
}

void ObjectManager::ClearAllObjects()
{
	for (int i = NONE_TAG; i < END_TAG; i++) {
		for (auto iter : ObjList[i])
		{
			iter->isDestroy = true;
		}
	}
}
