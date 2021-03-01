#include "DXUT.h"
#include "Player.h"

void Player::Init()
{
	//* anim Init *//
	{
		idle = new Animation(this, "p_idle");
		walk1 = new Animation(this, "p_walk");
		dash = new Animation(this, "p_dash");
		jump = new Animation(this, "p_jump");
		fall = new Animation(this, "p_fall");
		fall_repeat = new Animation(this, "p_fall_repeat");

		attack_a = new Animation(this, "p_attack_a");
		attack_b = new Animation(this, "p_attack_b");
		attack_c = new Animation(this, "p_attack_c");
		attack_d = new Animation(this, "p_attack_d");
		attack_e = new Animation(this, "p_attack_e");

		jump_attack = new Animation(this, "p_jump_attack");
		jump_attack_land = new Animation(this, "p_jump_attack_land");

		skill3_a = new Animation(this, "p_skill3_attack_a");
		skill3_b = new Animation(this, "p_skill3_attack_b");
	}

	//* combo Init *//
	{
		attack = new Combo(this, 'J');
		attack->AddCombo(attack_a);
		attack->AddCombo(attack_b);
		attack->AddCombo(attack_c);
		attack->AddCombo(attack_d);
		//attack->AddCombo(attack_e);

		skill3 = new Combo(this, 'K');
		skill3->AddCombo(skill3_a);
		skill3->AddCombo(skill3_b);
	}

	//* skill1 Init *//
	{
		skill1 = new Skill(this, "p_skill1", 'K');
		skill1->AddFrameEvent(0, 4, REF_LAMDA_VOID{
			Jump({2 * scale,-2});
			});
		skill1->AddFrameEvent(9, 9, REF_LAMDA_VOID{
			vPos.x -= 45 * scale;
			});
	}

	profile = new Profile(this);
	status = new UiWindow("status", VK_PAD_A, { 1,1 }, { 0,10 });
	status_power = new UiButton("power", REF_LAMDA_VOID{ invincibility = false; TIME->TimeScale = 1; status->WindowSwitch(); add_damage++; col2->damage = add_damage * level + 5; }, { 1,1 }, { -300,10 });
	status_hp = new UiButton("hp", REF_LAMDA_VOID{ invincibility = false; TIME->TimeScale = 1; status->WindowSwitch(); add_hp++; max_hp = add_hp * level + 50; hp = max_hp; }, { 1,1 }, { 300,10 });
	status->AddButton(status_power);
	status->AddButton(status_hp);

	k_cool = new Timer;
	k_cool->setTimer(5);
	sk_cool = new Timer;
	sk_cool->setTimer(3);
	l_cool = new Timer;
	l_cool->setTimer(0.5);

	hp = 50;
	max_hp = hp;
	damage = 5;
	level = 1;
	exp = 0;
	scale = 1;
	speed = 150;
	gravity = 200;
	invincibility = false;
	fall_flag = false;
	isGravity = false;
	move_dir = Vector2(0, 0);

	Collider::ColliderInit(this, &col, ObjectTag::PLAYER, 0, true);
	Collider::ColliderInit(this, &col2, ObjectTag::PATTACK, 5, false);
}

void Player::Update()
{
	status->WindowUpdate();

	k_cool->LockUpdate();
	sk_cool->LockUpdate();
	l_cool->LockUpdate();

	damage = col2->damage;

	if ((int)exp >= 10 /** (int)level + ((int)level - 1) * 10*/)
	{
		level++;
		exp -= 10;
		status->WindowSwitch();
	}

	if (status->isOpen())
	{
		invincibility = true;
		TIME->TimeScale = 0;
	}

	isGravity = true;

	CAMERA->m_vCameraPos = { 0,10 };

	//* hp if *//
	{
		if (hp > max_hp)
		{
			hp = max_hp;
		}
		else if (hp <= 0)
		{
			isDestroy = true;
		}
	}
	//* player body col setting *//
	{
		Vector2 temp_pos = { vPos.x + 6 * scale,vPos.y + 14 };
		Vector2 temp_size = { 40,70 };

		if (walk1->isKey)
		{
			temp_pos.x += 15 * scale;
		}
		if (dash->isKey)
		{
			temp_pos.x += 20 * scale;
			temp_pos.y += 7;
			temp_size = { 50,60 };
		}
		if (jump->isKey)
		{
			temp_pos.y -= 20;
		}
		if (fall_repeat->isKey || fall->isKey)
		{
			temp_pos.x += 10 * scale;
			temp_pos.y += 10;
		}

		col->SetRange(CAMERA->WorldToView(temp_pos), temp_size.x, temp_size.y);
		col2->SetRange(CAMERA->WorldToView({ temp_pos.x + 60 * scale,temp_pos.y}), 80, temp_size.y);
	}

	//* anim Update *//
	{
		idle->AnimUpdate();
		walk1->AnimUpdate();
		dash->AnimUpdate();
		jump->AnimUpdate();
		fall->AnimUpdate();
		fall_repeat->AnimUpdate();
		jump_attack->AnimUpdate();
		jump_attack_land->AnimUpdate();
	}

	//* combo Update *//
	{
		attack->ComboUpdate(nullptr);

		if (INPUT->KeyPress('S') && !skill1->skill_anim->isKey)
			skill3->ComboUpdate(&sk_cool);
	}

	//* skill Update *//
	{
		if (!skill3->IsKey())
			skill1->SkillUpdate(&k_cool);
	}

	//* idle if *//
	{
		if (!INPUT->AnyGameKeyDown())
		{
			idle->isKey = true;
		}
		else
		{
			idle->isKey = false;
		}
	}

	//* move if *//
	{
		if (vPos.x <= -500 + 30)
		{
			vPos.x = -500 + 31;
		}
		if (vPos.x >= 590 - 30)
		{
			vPos.x = 590 - 31;
		}

		vPos += move_dir * speed * D_TIME;

		if (INPUT->KeyPress('A') && INPUT->KeyPress('D'))
		{
			walk1->isKey = false;
			idle->isKey = true;
		}
		else if (INPUT->KeyPress('A'))
		{
			idle->isKey = false;

			if (!dash->isKey && !skill1->skill_anim->isKey && !skill3->IsKey())
				scale = -1;

			walk1->isKey = true;
		}
		else if (INPUT->KeyPress('D'))
		{
			idle->isKey = false;

			if (!dash->isKey && !skill1->skill_anim->isKey && !skill3->IsKey())
				scale = 1;

			walk1->isKey = true;
		}
		if (INPUT->KeyDown('A'))
		{
			move_dir.x--;
		}
		if (INPUT->KeyUp('A'))
		{
			walk1->isKey = false;
			move_dir.x++;
		}
		if (INPUT->KeyDown('D'))
		{
			move_dir.x++;
		}
		if (INPUT->KeyUp('D'))
		{
			walk1->isKey = false;
			move_dir.x--;
		}
	}

	//* gravity if *//
	{
		float ground = 160;

		if (!jump->isKey)
		{
			if (vPos.y < ground)
			{
				if (fall_flag)
				{
					fall->isKey = true;
					fall_repeat->isKey = false;
					fall_flag = false;
				}
				else
				{
					if (!fall->isKey)
					{
						fall_repeat->isKey = true;
					}
					else
					{
						idle->isKey = false;
						walk1->isKey = false;
					}
					if (fall_repeat->isKey)
					{
						idle->isKey = false;
						walk1->isKey = false;
					}
				}
			}
			else if (vPos.y >= ground /*&& vPos.y <= 21*/)
			{
				if (jump_attack->isKey)
				{
					jump_attack->isKey = false;
					jump_attack_land->isKey = true;
				}
				isGravity = false;
				fall_flag = true;
				fall->isKey = false;
				fall_repeat->isKey = false;
			}
		}
	}

	//* jump if *//
	{
		if (INPUT->KeyDown('W') && !skill1->skill_anim->isKey && !jump_attack->isKey && !jump_attack_land->isKey)
		{
			jump->isKey = true;
		}
		if (jump->isKey)
		{
			Jump({ 0,-2 });
			idle->isKey = false;
			walk1->isKey = false;
			fall_repeat->isKey = false;
			fall_flag = true;
			isGravity = false;
		}
	}

	//* combo attack if *//
	{
		if (attack->IsKey())
		{
			idle->isKey = false;
			walk1->isKey = false;
			jump->isKey = false;
			dash->isKey = false;
			fall->isKey = false;
			fall_repeat->isKey = false;
		}
	}

	//* skill1 if *//
	{
		if (skill1->skill_anim->isKey)
		{
			idle->isKey = false;
			fall->isKey = false;
			fall_repeat->isKey = false;
			walk1->isKey = false;
			attack->AllIsKeyFalse();
		}
	}

	//* dash if *//
	{
		invincibility = false;
		if (INPUT->KeyDown('L') && !dash->isKey && !skill1->skill_anim->isKey)
		{
			l_cool->isLock = false;
			dash->isKey = true;
		}
		if (dash->isKey)
		{
			vPos.x += (speed + 50) * scale * D_TIME;
			invincibility = true;
			idle->isKey = false;
			walk1->isKey = false;
			jump->isKey = false;
			fall->isKey = false;
			fall_repeat->isKey = false;
			skill1->skill_anim->isKey = false;
		}
	}

	//* skill3 if *//
	{
		if (skill3->IsKey())
		{
			idle->isKey = false;
			fall->isKey = false;
			fall_repeat->isKey = false;
			walk1->isKey = false;
			attack->AllIsKeyFalse();
			jump->isKey = false;
			dash->isKey = false;
		}
	}

	//* jump_attack if *//
	{
		if (isGravity && !skill1->skill_anim->isKey)
		{
			attack->AllIsKeyFalse();

			if (INPUT->KeyDown('J'))
			{
				jump_attack->isKey = true;
			}
			if (jump_attack->isKey && !jump_attack_land->isKey)
			{
				Jump({ 0,2 });
				idle->isKey = false;
				fall->isKey = false;
				fall_repeat->isKey = false;
				walk1->isKey = false;
				jump->isKey = false;
			}
		}
	}

	//* jump_attack_land if *//
	{
		if (jump_attack_land->isKey)
		{
			idle->isKey = false;
			walk1->isKey = false;
			dash->isKey = false;
			attack->AllIsKeyFalse();
			skill1->skill_anim->isKey = false;
			jump->isKey = false;
		}
	}

	if (isGravity)
		vPos.y += gravity * D_TIME;
}

void Player::Render()
{
	status->WindowRender();

	if (status->isOpen())
	{
		IMAGE->drawText("plus power", { -300, 150 }, 50, RGB(255, 255, 255), true);
		IMAGE->drawText("plus hp", { 300, 150 }, 50, RGB(255, 255, 255), true);
	}

	if (TIME->TimeScale == 0)
		return;
	//* anim Render *//
	{
		idle->AnimRender(vPos, 0, { 2 * scale,2 });
		walk1->AnimRender(vPos, 0, { 2 * scale,2 });
		dash->AnimRender({vPos.x + 20 * scale,vPos.y + 20}, 0, { 2 * scale,2 }, false);
		jump->AnimRender(vPos, 0, { 2 * scale,2 }, false);
		fall->AnimRender(vPos, 0, { 2 * scale,2 }, false);
		fall_repeat->AnimRender(vPos, 0, { 2 * scale,2 });
		jump_attack->AnimRender(vPos, 0, { 2 * scale,2 }, false);
		jump_attack_land->AnimRender(vPos, 0, { 2 * scale, 2 }, false);
	}

	//* combo Render *//
	{
		attack->ComboRender();
		if (attack->IsKey())
		{
			if (first_flag)
			{
				first_flag = false;
				col2->Enable();
			}
		}
		else
		{
			if (!first_flag)
			{
				first_flag = true;
				col2->UnEnable();
			}
		}
	}

	//* skill3 Render *//
	{
		skill3->ComboRender();
		if (skill3->IsKey())
		{
			sk_cool->isLock = false;

			if (first_flag)
			{
				first_flag = false;
				col2->Enable();
			}
			else
			{
				if (!first_flag)
				{
					first_flag = true;
					col2->UnEnable();
				}
			}
		}
	}

	//* skill1 Render *//
	{
		skill1->SkillRender();
		if (skill1->skill_anim->isKey)
		{
			k_cool->isLock = false;

			if (first_flag)
			{
				first_flag = false;
				col2->Enable();
			}
			else
			{
				if (!first_flag)
				{
					first_flag = true;
					col2->UnEnable();
				}
			}
		}
	}

	profile->ProfileRender();

	char str[256];

	IMAGE->FindImage("key_bg")->CenterRender({ -200 ,10 + 280 }, 0, { 3,3 }, 1, RGBA(255, 255, 255, j_alpha));
	IMAGE->drawText("J", { -200 ,10 + 280 }, 50, RGBA(255, 255, 255, 255), true);
	sprintf(str, "%.1f", 0.0);
	IMAGE->drawText(str, { -200 ,10 + 280 + 60 }, 50, RGBA(255, 255, 255, 255), true);

	IMAGE->FindImage("key_bg")->CenterRender({ -65 ,10 + 280 }, 0, { 3,3 }, 1, RGBA(255, 255, 255, (int)(-(k_cool->m_start - k_cool->m_delay) * 51)));
	IMAGE->drawText("K", { -65 ,10 + 280 }, 50, RGBA(255, 255, 255, 255), true);
	sprintf(str, "%.1f", -(k_cool->m_start - k_cool->m_delay));
	IMAGE->drawText(str, { -65 ,10 + 280 + 60 }, 50, RGBA(255, 255, 255, 255), true);

	IMAGE->FindImage("key_bg")->CenterRender({ 65 ,10 + 280 }, 0, { 3,3 }, 1, RGBA(255, 255, 255, (int)(-(sk_cool->m_start - sk_cool->m_delay) * 85)));
	IMAGE->drawText("S+K", { 65 ,10 + 280 }, 30, RGBA(255, 255, 255, 255), true);
	sprintf(str, "%.1f", -(sk_cool->m_start - sk_cool->m_delay));
	IMAGE->drawText(str, { 65 ,10 + 280 + 60 }, 50, RGBA(255, 255, 255, 255), true);

	IMAGE->FindImage("key_bg")->CenterRender({ 200 ,10 + 280 }, 0, { 3,3 }, 1, RGBA(255, 255, 255, (int)(-(l_cool->m_start - l_cool->m_delay) * 510)));
	IMAGE->drawText("L", { 200 ,10 + 280 }, 50, RGBA(255, 255, 255, 255), true);
	sprintf(str, "%.1f", -(l_cool->m_start - l_cool->m_delay));
	IMAGE->drawText(str, { 200 ,10 + 280 + 60 }, 50, RGBA(255, 255, 255, 255), true);

	col->Draw(0, 255, 0);
	col2->Draw(0, 255, 255);
}

void Player::Release()
{
	SAFE_DELETE(col);
	SAFE_DELETE(col2);

	//* anim Release *//
	{
		SAFE_DELETE(idle);
		SAFE_DELETE(walk1);
		//SAFE_DELETE(walk2);
		SAFE_DELETE(dash);
		SAFE_DELETE(jump);
		SAFE_DELETE(fall);
		SAFE_DELETE(fall_repeat);

		SAFE_DELETE(attack_a);
		SAFE_DELETE(attack_b);
		SAFE_DELETE(attack_c);
		SAFE_DELETE(attack_d);
		SAFE_DELETE(attack_e);

		SAFE_DELETE(jump_attack);
		SAFE_DELETE(jump_attack_land);

		SAFE_DELETE(skill3_a);
		SAFE_DELETE(skill3_b);
	}

	//* combo Release *//
	{
		SAFE_DELETE(attack);
		SAFE_DELETE(skill3);
	}

	//* skill Release *//
	{
		SAFE_DELETE(skill1);
	}

	SAFE_DELETE(profile);
	SAFE_DELETE(status);

	SAFE_DELETE(k_cool);
	SAFE_DELETE(sk_cool);
	SAFE_DELETE(l_cool);
}

void Player::onCollisionStay(Collider* col)
{
	if (!invincibility)
	{
		switch (col->m_tag)
		{
		case EATTACK:
			CAMERA->CameraShake(0.5f);
			KnockBack(NearObject(ENEMY), 1500);
			hp -= col->damage;
			break;
		}
		col->UnEnable();
	}
}

void Player::onCollisionExit(Collider* col)
{
}