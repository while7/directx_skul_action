#include "DXUT.h"
#include "Charge.h"

int Charge::REF_COUNT = 0;

void Charge::ChargeUpdate()
{
	if (end_flag)
		return; // charge�� �������Ƿ� Update�� ���ϰ� return��

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


	if (iter == charge_list.end()) // iter++�� �ϴٰ� end�� ������ ��� -> charge�� ����
	{
		for (auto& anim : charge_list)
		{
			if (anim != nullptr)
			{
				anim->isKey = false; // charge�� ������ ���� key���� ���� false�� ����
			}
		}
		end_flag = true; // ���� �˸��� flag�� true�� �ٲ�
	}
}

void Charge::ChargeRender(Vector2 pos, Vector2 size)
{
	if (end_flag)
		return; // charge�� �������Ƿ� Render�� ���ϰ� return��

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
		return; // charge�� �������Ƿ� �ٸ� �ൿ�� ������ ��

	cancel_flag = true;
}

void Charge::Start()
{
	if (end_flag)
	{
		end_flag = false; // ���� ���������� ���� �˸��� flag�� false�� ���� �����۵��ϰ� ����

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
