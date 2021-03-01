#include "DXUT.h"
#include "Skill.h"

int Skill::REF_COUNT = 0;

void Skill::AddFrameEvent(UINT min, UINT max, function<void()> func)
{
	for (size_t i = min; i <= max; i++)
	{
		frame_evnet_list.insert(make_pair(i, func));
	}
}

void Skill::SkillUpdate(Timer** timer)
{
	if (timer != nullptr)
	{
		if (-((*timer)->m_start - (*timer)->m_delay) == (*timer)->m_delay)
		{
			if (INPUT->KeyPress(key) && !skill_anim->isKey)
			{
				(*timer)->isLock = false;
				skill_anim->isKey = true;
				owner->isStun = true;
			}
			else if (!skill_anim->isKey && owner->isStun)
			{
				owner->isStun = false;
			}
		}
	}
	else
	{
		if (INPUT->KeyPress(key) && !skill_anim->isKey)
		{
			skill_anim->isKey = true;
			owner->isStun = true;
		}
		else if (!skill_anim->isKey && owner->isStun)
		{
			owner->isStun = false;
		}
	}

	skill_anim->AnimUpdate();
	if (skill_anim->isKey)
	{
		iter = frame_evnet_list.find(skill_anim->index);
		if (iter != frame_evnet_list.end())
		{
			(*iter).second();
		}
	}
}

void Skill::SkillRender(Vector2 add)
{
	skill_anim->AnimRender(owner->vPos + add, 0, { 2 * owner->scale ,2 }, false);
}