#include "DXUT.h"
#include "Patterns.h"

Patterns::Patterns(Object* owner)
	:owner(owner)
{
	alpha = 255;

	case1 = true;
	case2 = true;
	case3 = true;
	case4 = true;
	case5 = true;
	case6 = true;

	appear_flag = false;

	x_scale = 1;

	this->owner = owner;
	player = OBJECT->FindObject("player");

	anim_list.clear();

	idle = new Animation(owner, "b_idle");

	anim_list = 
	{
		appear = new Animation(owner, "b_appear"),
		attack_a = new Animation(owner, "b_attack_a"),
		attack_b = new Animation(owner, "b_attack_b"),
		attack_c = new Animation(owner, "b_attack_c"),
		dash = new Animation(owner, "b_dash"),
		diagonal = new Animation(owner, "b_diagonal"),
		diagonal_fin = new Animation(owner, "b_diagonal_fin"),
		disappear = new Animation(owner, "b_disappear"),
		rush = new Animation(owner, "b_rush"),
		slash_h = new Animation(owner, "b_slash_h"),
		slash_v = new Animation(owner, "b_slash_v"),
	};

	delay = new Timer;
	delay->setTimer(1);
}

Patterns::~Patterns()
{
	SAFE_DELETE(appear);
	SAFE_DELETE(attack_a);
	SAFE_DELETE(attack_b);
	SAFE_DELETE(attack_c);
	SAFE_DELETE(dash);
	SAFE_DELETE(diagonal);
	SAFE_DELETE(diagonal_fin);
	SAFE_DELETE(disappear);
	SAFE_DELETE(idle);
	SAFE_DELETE(rush);
	SAFE_DELETE(slash_h);
	SAFE_DELETE(slash_v);

	SAFE_DELETE(delay);
}

void Patterns::Update()
{
	for (auto& iter : anim_list)
		iter->AnimUpdate();
	idle->AnimUpdate();

	if (delay->Update())
	{
		case1 = true;
		case2 = true;
		case3 = true;
		case4 = true;
		case5 = true;
		case6 = true;
	}

	//if (HpPerIsIn(100, 75))
	//{
	//}
	if (HpPerIsIn(100, 50))
	{
		if (case1)
			if (SetAppear())
				Case1(case1);
	}
	//else if (HpPerIsIn(75, 50))
	//{
	//}
	else if (HpPerIsIn(50, 0))
	{
		if (case2)
			if (SetAppear())
				Case2(case2);
	}

	if (IsIdle())
		idle->isKey = true;
	else
		idle->isKey = false;
}

void Patterns::Render()
{
	for (auto& iter : anim_list)
		iter->AnimRender(owner->vPos, 0, { 2 * x_scale,2 }, false, RGBA(255, 255, 255, alpha));
	idle->AnimRender(owner->vPos, 0, { 2 * x_scale,2 }, true, RGBA(255, 255, 255, alpha));
}

bool Patterns::HpPerIsIn(int max_per, int min_per)
{
	if ((owner->max_hp * max_per / 100) >= owner->hp &&
		owner->hp >= (owner->max_hp * min_per / 100))
	{
		return true;
	}
	return false;
}

bool Patterns::IsIdle()
{
	if (appear->isKey || attack_a->isKey || attack_b->isKey || 
		attack_c->isKey || dash->isKey || diagonal->isKey || 
		diagonal_fin->isKey || disappear->isKey || rush->isKey || 
		slash_h->isKey || slash_v->isKey)
		return false;
	return true;
}

bool Patterns::Appear(bool idle_flag)
{
	if (alpha == 0)
	{
		if (idle_flag)
		{
			owner->vPos = { 0, 160 };
		}
		else
		{
			owner->vPos = player->vPos;
			appear->isKey = true;
		}
	}
	
	alpha += 5;
	if (alpha >= 255)
	{
		alpha = 255;
		appear_flag = false;
		return true;
	}

	return false;
}

bool Patterns::Disappear()
{
	if (alpha == 255)
		disappear->isKey = true;
	alpha -= 5;
	if (alpha <= 0)
	{
		alpha = 0;
		appear_flag = true;
		return true;
	}
	return false;
}

bool Patterns::SetAppear(bool idle_flag)
{
	if (!appear_flag)
	{
		Disappear();
	}
	if (appear_flag)
	{
		if (Appear(idle_flag))
			return true;
	}
	return false;
}

bool Patterns::Case1(bool& flag)
{
	Debug("Case1");

	slash_h->isKey = true;

	flag = false;
	return false;
}

bool Patterns::Case2(bool& flag)
{
	Debug("Case2");

	slash_v->isKey = true;

	flag = false;
	return false;
}

bool Patterns::Case3()
{
	return false;
}

bool Patterns::Case4()
{
	return false;
}

bool Patterns::Case5()
{
	return false;
}

bool Patterns::Case6()
{
	return false;
}