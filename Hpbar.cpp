#include "DXUT.h"
#include "Hpbar.h"

int Hpbar::REF_COUNT = 0;

Hpbar::Hpbar(Object* owner, Vector2 pos, D3DXCOLOR color)
	:owner(owner), pos(pos), color(color)
{
	this->owner = owner;
	this->pos = pos;
	this->color = color;

	hpbar = IMAGE->FindImage("whitebar");

	REF_COUNT++;
}

Hpbar::~Hpbar()
{
	REF_COUNT--;
	Debug("---------------------------------- [ ~Hpbar()     REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
	if (REF_COUNT == 0)
		Debug("Hpbar REF_COUNT is ZERO!");
}

void Hpbar::HpbarRender(bool isBoss)
{
	char str[200];
	//hpbar->Render(owner->vPos + pos, 0, { 1,1 }, (1 / owner->vPos.y) <= 0 ? 0 : (1 / owner->vPos.y), RGBA(r, g, b, a));
	//hpbar->Render(owner->vPos + pos/* + Vector2(hpbar->info.Width, 0)*/, 0, { -2,1 }, (1 / owner->vPos.y) <= 0 ? 0 : (1 / owner->vPos.y), RGBA(0, 0, 0, 255));
	if (isBoss)
	{
		hpbar->Render(Vector2(CAMERA->m_vCameraPos.x - center_vec2.x + 10,CAMERA->m_vCameraPos.y - center_vec2.y), 0, { 1,1 }, { -630,-10,630,10 }, RGBA(0, 0, 0, 255));
		hpbar->Render(Vector2(CAMERA->m_vCameraPos.x - center_vec2.x + 10, CAMERA->m_vCameraPos.y - center_vec2.y), 0, { (float)owner->hp / (float)owner->max_hp,1.0f }, { -630,-10,630,10 }, color);

		sprintf(str, "%d / %d", owner->hp, owner->max_hp);
		IMAGE->drawText(str, Vector2(CAMERA->m_vCameraPos.x, CAMERA->m_vCameraPos.y - center_vec2.y + 5), 30, RGBA(255, 255, 255, 255), true);
	}
	else
	{
		hpbar->Render(owner->vPos + pos - Vector2(50, 0), 0, { 1,1 }, { -50,-10,50,10 }, RGBA(0, 0, 0, 255));
		hpbar->Render(owner->vPos + pos - Vector2(50, 0), 0, { (float)owner->hp / (float)owner->max_hp,1.0f }, { -50,-10,50,10 }, color);

		sprintf(str, "%d / %d", owner->hp, owner->max_hp);
		IMAGE->drawText(str, owner->vPos + pos + Vector2(7, 10), 20, RGBA(255, 255, 255, 255), true);
	}

	sprintf(str, "lv.%.0f", owner->level);
	IMAGE->drawText(str, owner->vPos + pos + Vector2(-35, -5), 20, RGBA(0, 0, 0, 255), true);
	sprintf(str, "(exp:%.0f)", owner->exp);
	IMAGE->drawText(str, owner->vPos + pos + Vector2(10, -10), 10, RGBA(0, 0, 0, 255), true);
}