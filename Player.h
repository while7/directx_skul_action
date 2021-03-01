#pragma once
#include "Object.h"
class Player :
    public Object
{
    Animation* idle;
    Animation* walk1;
    //Animation* walk2;
    Animation* dash;
    Animation* jump;
    Animation* fall;
    Animation* fall_repeat;

    Combo* attack;
    Animation* attack_a;
    Animation* attack_b;
    Animation* attack_c;
    Animation* attack_d;
    Animation* attack_e;

    Skill* skill1;

    Animation* jump_attack;
    Animation* jump_attack_land;

    Combo* skill3;
    Animation* skill3_a;
    Animation* skill3_b;

    Vector2 move_dir;

    Profile* profile;

    UiWindow* status;
    UiButton* status_power;
    UiButton* status_hp;

    bool fall_flag;
    bool first_flag = true;

    Timer* k_cool;
    Timer* sk_cool;
    Timer* l_cool;

    int j_alpha = 255;
    int k_alpha = 255;
    int sk_alpha = 255;
    int l_alpha = 255;

    // Object을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void onCollisionStay(Collider* col) override;
    virtual void onCollisionExit(Collider* col) override;
};