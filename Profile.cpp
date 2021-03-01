#include "DXUT.h"
#include "Profile.h"

int Profile::REF_COUNT = 0;

Profile::Profile(Object* owner)
	:owner(owner)
{
	profile = IMAGE->FindImage("profile");
	bar = IMAGE->FindImage("whitebar");

	REF_COUNT++;
}

Profile::~Profile()
{
	REF_COUNT--;
	Debug("---------------------------------- [ ~Profile()     REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
	if (REF_COUNT == 0)
		Debug("Profile REF_COUNT is ZERO!");
}

void Profile::ProfileRender()
{
	char str[256];

	RECT bar_rect = { -150,-10,150,10 };

	bar->CenterRender({ -center_vec2.x + 85,10 - center_vec2.y + 85 }, 0, { 10,9 }, 1, RGBA(153, 0, 255, 150));

	Vector2 hp_pos = { -center_vec2.x + 240,10 - center_vec2.y + 40 };
	{
		bar->Render(hp_pos, 0, { 1,1 }, bar_rect, RGBA(0, 0, 0, 255));
		bar->Render(hp_pos, 0, { (float)owner->hp / (float)owner->max_hp,1.0f }, bar_rect, RGB(0, 255, 0));
		sprintf(str, "%d / %d (+ %d)", owner->hp, owner->max_hp, owner->add_hp);
		IMAGE->drawText(str, { hp_pos.x + bar_rect.right,hp_pos.y + bar_rect.bottom }, 20, RGBA(100, 100, 100, 255), true);
		IMAGE->drawText("H P", { hp_pos.x - 40,hp_pos.y + bar_rect.bottom - 3 }, 50, RGBA(255, 255, 255, 255), true);
	}

	Vector2 exp_pos = { hp_pos.x,hp_pos.y + 25 };
	{
		bar->Render(exp_pos, 0, { 1,1 }, bar_rect, RGBA(0, 0, 0, 255));
		bar->Render(exp_pos, 0, { (float)owner->exp / 10.0f,1.0f }, bar_rect, RGB(255, 255, 0));
		sprintf(str, "%f / %d", owner->exp, 10);
		IMAGE->drawText(str, { exp_pos.x + bar_rect.right,exp_pos.y + bar_rect.bottom }, 20, RGBA(100, 100, 100, 255), true);
		IMAGE->drawText("EXP", { exp_pos.x - 40,exp_pos.y + bar_rect.bottom + 3 }, 50, RGBA(255, 255, 255, 255), true);
	}

	profile->CenterRender({ -center_vec2.x + 85,10 - center_vec2.y + 85 }, 0, { 4,4 }, 1);
	sprintf(str, "Lv. %d", (int)owner->level);
	IMAGE->drawText(str, { -center_vec2.x + 460,10 - center_vec2.y + 120 }, 60, RGBA(255, 255, 255, 255), true);

	sprintf(str, "Power %d (+%2d)", (int)owner->damage, owner->add_damage);
	IMAGE->drawText(str, { -center_vec2.x + 260,10 - center_vec2.y + 125 }, 30, RGBA(255, 255, 255, 255), true);
}