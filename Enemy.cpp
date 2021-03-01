#include "DXUT.h"
#include "Enemy.h"

/*
	switch (type)
	{
	case EnemyType::Article:
		break;
	case EnemyType::Hunter:
		break;
	case EnemyType::Wizard:
		break;
	case EnemyType::Boss:
		break;
	}
*/

Enemy::Enemy(EnemyType type)
	:type(type)
{
}

void Enemy::Init()
{
	delay = new Timer;

	player = OBJECT->FindObject("player");

	anim_list.clear();
	skill_list.clear();

	hp = 10;
	max_hp = hp;
	level = 1;
	exp = 0;

	switch (type)
	{
	case EnemyType::Article:
	{
		range_x = 20; speed_x = 50;

		ca_charging = new Animation(this, "a_ca_charging");	
		ca_completed = new Animation(this, "a_ca_completed");

		anim_list = {
			dash = new Animation(this, "a_dash"),
			fall = new Animation(this, "a_fall"),
			fall_repeat = new Animation(this, "a_fall_repeat"),
			idle = new Animation(this, "a_idle"),
			jump = new Animation(this, "a_jump"),
			jump_attack = new Animation(this, "a_jump_attack"),
			walk = new Animation(this, "a_walk"),
		};

		charge = new Charge(this, ca_prepare, ca_anticipation, ca_charging, ca_charged, ca_incompleted, ca_completed);
	}
		break;
	case EnemyType::Hunter:
	{
		range_x = 150; speed_x = 30;

		ca_anticipation = new Animation(this, "h_ca_anticipation");
		ca_charged = new Animation(this, "h_ca_charged");
		ca_charging = new Animation(this, "h_ca_charging");
		ca_completed = new Animation(this, "h_ca_completed");
		ca_incompleted = new Animation(this, "h_ca_incompleted");
		ca_prepare = new Animation(this, "h_ca_prepare");

		anim_list = {
			dash = new Animation(this, "h_dash"),
			fall = new Animation(this, "h_fall"),
			fall_repeat = new Animation(this, "h_fall_repeat"),
			fs_attack = new Animation(this, "h_fs_attack"),
			fs_ready = new Animation(this, "h_fs_ready"),
			idle = new Animation(this, "h_idle"),
			jump = new Animation(this, "h_jump"),
			jump_attack = new Animation(this, "h_jump_attack"),
			ss_attack = new Animation(this, "h_ss_attack"),
			ss_ready = new Animation(this, "h_ss_ready"),
			walk = new Animation(this, "h_walk"),
		};

		charge = new Charge(this, ca_prepare, ca_anticipation, ca_charging, ca_charged, ca_incompleted, ca_completed);
	}
		break;
	case EnemyType::Wizard:
	{
		range_x = 300; speed_x = 15;

		delay->setTimer(3);

		anim_list = {
			dash = new Animation(this, "w_dash"),
			fall = new Animation(this, "w_fall"),
			fall_repeat = new Animation(this, "w_fall_repeat"),
			idle = new Animation(this, "w_idle"),
			jump = new Animation(this, "w_jump"),
			walk = new Animation(this, "w_walk"),
		};
		skill_list = {
			skill1 = new Skill(this, "w_skill1"),
			skill2 = new Skill(this, "w_skill2"),
			skill3 = new Skill(this, "w_skill3"),
			skill4 = new Skill(this, "w_skill4"),
		};
	}
		break;
	case EnemyType::Boss:
	{
		idle = new Animation(this, "null");
		walk = new Animation(this, "null");
		patterns = new Patterns(this);

		level = player->level;
	}
		break;
	}

	idle->isKey = true;
	profile = new Hpbar(this, { 0,-50 }, RGB(255, 0, 100));
	Collider::ColliderInit(this, &col, ENEMY, 0, true);
	Collider::ColliderInit(this, &col2, EATTACK, 1, false);
}

void Enemy::Update()
{
	col2->UnEnable();

	if ((int)exp >= 10)
	{
		level++;
		exp = 0;
	}

	exp += D_TIME;

	col->SetRange(CAMERA->WorldToView(vPos), 50, 50);
	col2->SetRange(CAMERA->WorldToView(Vector2({vPos.x + 40 * scale, vPos.y})), 25, 50);

	if (hp > max_hp)
	{
		hp = max_hp;
	}

	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 4);

	delay->LockUpdate();

	x_axis = AdjustXAxis(player, range_x);

	for (auto& iter : anim_list)
		iter->AnimUpdate();
	for (auto& iter : skill_list)
		iter->SkillUpdate(nullptr);

	if (patterns != nullptr)
		patterns->Update();

	if (x_axis == 0)
		can_attack = true;
	else
		can_attack = false;

	if (can_attack)
	{
		idle->isKey = true;
		walk->isKey = false;
	}
	else
	{
		if (!first_flag)
			first_flag = true;

		idle->isKey = false;
		walk->isKey = true;

		if (skill1 != nullptr)
			skill1->skill_anim->isKey = false;
		if (skill2 != nullptr)
			skill2->skill_anim->isKey = false;
		if (skill3 != nullptr)
			skill3->skill_anim->isKey = false;
		if (skill4 != nullptr)
			skill4->skill_anim->isKey = false;
	}

	switch (type)
	{
	case EnemyType::Article:
	{
		charge->ChargeUpdate();

		if (can_attack)
		{
			charge->Start();

			idle->isKey = false;
			walk->isKey = false;
		}

		if (charge->IsKey())
		{
			if (first_flag)
			{
				first_flag = false;
				col2->Enable();
			}
			idle->isKey = false;
			walk->isKey = false;
		}
	}
		break;
	case EnemyType::Hunter:
	{
		charge->ChargeUpdate();

		if (can_attack)
		{
			charge->Start();

			idle->isKey = false;
			walk->isKey = false;
		}

		if (charge->IsKey())
		{
			if (first_flag)
			{
				first_flag = false;
				col2->Enable();
			}
			idle->isKey = false;
			walk->isKey = false;
		}
	}
		break;
	case EnemyType::Wizard:
	{
		if (can_attack)
		{
			if (!skill1->skill_anim->isKey &&
				!skill2->skill_anim->isKey &&
				!skill3->skill_anim->isKey &&
				!skill4->skill_anim->isKey && delay->isLock)
			{
				int skill_type = dis(gen);
				switch (skill_type)
				{
				case 1:
					skill1->skill_anim->isKey = true;
					break;
				case 2:
					skill2->skill_anim->isKey = true;
					break;
				case 3:
					skill3->skill_anim->isKey = true;
					break;
				case 4:
					skill4->skill_anim->isKey = true;
					break;
				}
			}

			if (skill1->skill_anim->isKey ||
				skill2->skill_anim->isKey ||
				skill3->skill_anim->isKey ||
				skill4->skill_anim->isKey)
			{
				idle->isKey = false;
				walk->isKey = false;

				delay->isLock = false;

				col2->Enable();
			}
		}
	}
		break;
	case EnemyType::Boss:
	{

	}
		break;
	}

	vPos += Vector2(x_axis * speed_x, 0) * D_TIME;
}

void Enemy::Render()
{
	if (TIME->TimeScale == 0)
		return;
	for (auto& iter : anim_list)
		iter->AnimRender(vPos, 0, { 2 * scale,2 });
	for (auto& iter : skill_list)
		iter->SkillRender();

	if (patterns != nullptr)
		patterns->Render();

	switch (type)
	{
	case EnemyType::Article:
	{
		charge->ChargeRender(vPos, { 2 * scale,2 });
	}
		break;
	case EnemyType::Hunter:
	{
		charge->ChargeRender(vPos, { 2 * scale,2 });
	}
		break;
	case EnemyType::Wizard:
		break;
	case EnemyType::Boss:
		break;
	}

	profile->HpbarRender();
	col->Draw(255, 0, 0);
	col2->Draw(255, 255, 0);
}

void Enemy::Release()
{
	SAFE_DELETE(col);
	SAFE_DELETE(col2);

	SAFE_DELETE(charge);
	SAFE_DELETE(idle);
	SAFE_DELETE(walk);
	SAFE_DELETE(jump);
	SAFE_DELETE(dash);
	SAFE_DELETE(fall);
	SAFE_DELETE(fall_repeat);
	SAFE_DELETE(jump_attack);
	SAFE_DELETE(fs_ready);
	SAFE_DELETE(fs_attack);
	SAFE_DELETE(ss_ready);
	SAFE_DELETE(ss_attack);
	SAFE_DELETE(skill1);
	SAFE_DELETE(skill2);
	SAFE_DELETE(skill3);
	SAFE_DELETE(skill4);
	SAFE_DELETE(delay);

	SAFE_DELETE(profile);
	SAFE_DELETE(patterns);

	anim_list.clear();
	skill_list.clear();
}

void Enemy::onCollisionStay(Collider* col)
{
	switch (type)
	{
	case EnemyType::Article:
	case EnemyType::Hunter:
	{
		switch (col->m_tag)
		{
		case PATTACK:
			hp -= col->damage;
			col->UnEnable();
			charge->ChargeCancel();
			break;
		}
	}
		break;
	case EnemyType::Wizard:
	{
		switch (col->m_tag)
		{
		case PATTACK:
			hp -= col->damage;
			col->UnEnable();
			break;
		}
	}
		break;
	case EnemyType::Boss:
	{

	}
		break;
	}

	if (hp <= 0)
	{
		if (!isDestroy)
		{
			col->lpGameObject->exp += level / col->lpGameObject->level;
			isDestroy = true;
		}
	}
}

void Enemy::onCollisionExit(Collider* col)
{
}