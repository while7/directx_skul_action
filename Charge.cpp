#include "DXUT.h"
#include "Charge.h"

int Charge::REF_COUNT = 0;

void Charge::ChargeUpdate()
{
	if (end_flag)
		return; // charge가 끝났으므로 Update를 못하게 return함

	(*iter)->AnimUpdate();

	if ((*iter) != nullptr)
	{
		if ((*iter)->isKey)
		{
			return;
		}
		else
		{
			iter++;

			if (iter != charge_list.end())
			{
				if ((*iter) != nullptr)
				{
					if (cancel_flag)
					{
						if ((*iter) == charge_list[COMPLETED])
						{
							(*iter)->isKey = false;
							iter++;
						}
					}
					else
					{
						if ((*iter) == charge_list[INCOMPLETED])
						{
							(*iter)->isKey = false;
							iter++;
						}
					}

					if (iter != charge_list.end())
						(*iter)->isKey = true;
				}
			}
		}
	}

	if (iter != charge_list.end())
	{
		if ((*iter) == nullptr)
		{
			while ((*iter) == nullptr)
			{
				iter++;
			}
			(*iter)->isKey = true;
		}
	}


	if (iter == charge_list.end()) // iter++을 하다가 end랑 같아진 경우 -> charge를 끝냄
	{
		for (auto& anim : charge_list)
		{
			if (anim != nullptr)
			{
				anim->isKey = false; // charge를 끝내기 위해 key값을 전부 false를 해줌
			}
		}
		end_flag = true; // 끝을 알리는 flag를 true로 바꿈
	}
}

void Charge::ChargeRender(Vector2 pos, Vector2 size)
{
	if (end_flag)
		return; // charge가 끝났으므로 Render를 못하게 return함

	if (iter != charge_list.end())
	{
		if ((*iter) != nullptr)
		{
			if ((*iter)->isKey)
			{
				(*iter)->AnimRender(pos, 0, size, false);
			}
		}
	}
}

void Charge::ChargeCancel()
{
	if (end_flag)
		return; // charge가 끝났으므로 다른 행동에 제한을 둠

	cancel_flag = true;
}

void Charge::Start()
{
	if (end_flag)
	{
		end_flag = false; // 새로 시작했으니 끝을 알리는 flag를 false로 만들어서 정상작동하게 만듦

		iter = charge_list.begin();

		for (size_t i = 0; i < COMPLETED + 1; i++)
		{
			if ((*iter) != nullptr)
			{
				(*iter)->isKey = true;
				return;
			}

			iter++;
		}
	}
}

bool Charge::IsKey()
{
	for (auto& anim : charge_list)
	{
		if (anim != nullptr)
			if (anim->isKey)
				return true;
	}
	return false;
}
