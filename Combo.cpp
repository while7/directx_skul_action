#include "DXUT.h"
#include "Combo.h"

int Combo::REF_COUNT = 0;

void Combo::ComboUpdate(Timer** timer)
{
	next_combo_timer->LockUpdate();

	if (INPUT->KeyPress(bind_key)) // ���� ������ Ű�� ������ ���
	{
		if (!(*iter)->isKey) // iter�� ����Ű�� anim�� iskey�� false�� ��� -> ���ϸ��̼��� �����ų� ó���� ���
		{
			if (next_combo_timer->isLock) // Ÿ�̸Ӱ� ������ -> ó�� / �޺��� �ٽ� �����ؾ��ϴ� ���
			{
				iter = combo_list.begin();
				for (auto iter : combo_list)
				{
					iter->isKey = false;
				}
				index = 0;
			}
			else // Ÿ�̸Ӱ� �����ִ°�� -> ���� �޺��� ���°� ��ȿ�� ���
			{
				iter++; // ���� �޺��� �ű�

				if (iter == combo_list.end()) // iter�� ��ȿ���� ���� ������ ����Ų�ٸ�
				{
					iter = combo_list.begin(); // iter�� list�� ó������ �ٲ���
				}

				index = 0; // index �ʱ�ȭ
			}

			(*iter)->isKey = true; // iter�� ����Ű�� anim�� iskey�� true�� �ٲ���
		}
		next_combo_timer->isLock = false; // �����޺��� ���� ��ȿ�ð� Ÿ�̸Ӹ� ���� -> �� ���� true�� ��
	}
}

void Combo::ComboRender()
{
	{
		(*iter)->AnimUpdate();
		(*iter)->AnimRender(owner->vPos, 0, { 2 * owner->scale,2 }, false);
	}
}

void Combo::AllIsKeyFalse()
{
	for (auto iter : combo_list)
	{
		iter->isKey = false;
	}
}

bool Combo::IsKey()
{
	for (auto iter : combo_list)
	{
		if (iter->isKey)
			return true;
	}
	return false;
}

int Combo::Index()
{
	return index;
}

int Combo::Frame()
{
	return (*iter)->index;
}
