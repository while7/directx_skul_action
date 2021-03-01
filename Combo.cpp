#include "DXUT.h"
#include "Combo.h"

int Combo::REF_COUNT = 0;

void Combo::ComboUpdate(Timer** timer)
{
	next_combo_timer->LockUpdate();

	if (INPUT->KeyPress(bind_key)) // 내가 설정한 키를 눌렀을 경우
	{
		if (!(*iter)->isKey) // iter가 가르키는 anim의 iskey가 false인 경우 -> 에니메이션이 끝나거나 처음인 경우
		{
			if (next_combo_timer->isLock) // 타이머가 멈춘경우 -> 처음 / 콤보를 다시 시작해야하는 경우
			{
				iter = combo_list.begin();
				for (auto iter : combo_list)
				{
					iter->isKey = false;
				}
				index = 0;
			}
			else // 타이머가 돌고있는경우 -> 다음 콤보로 가는게 유효한 경우
			{
				iter++; // 다음 콤보로 옮김

				if (iter == combo_list.end()) // iter가 유효하지 않은 공간을 가르킨다면
				{
					iter = combo_list.begin(); // iter를 list의 처음으로 바꿔줌
				}

				index = 0; // index 초기화
			}

			(*iter)->isKey = true; // iter가 가르키는 anim의 iskey를 true로 바꿔줌
		}
		next_combo_timer->isLock = false; // 다음콤보로 가는 유효시간 타이머를 돌림 -> 다 돌면 true가 됨
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
