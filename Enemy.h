#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
    Enemy(EnemyType type);
private:
    EnemyType type;

    Object* player = nullptr;

    Animation* idle = nullptr;
    Animation* walk = nullptr;
    Animation* jump = nullptr;
    Animation* dash = nullptr;
    Animation* fall = nullptr;
    Animation* fall_repeat = nullptr;
    Animation* jump_attack = nullptr;
    Animation* ca_prepare = nullptr;
    Animation* ca_anticipation = nullptr;
    Animation* ca_charging = nullptr;
    Animation* ca_charged = nullptr;
    Animation* ca_incompleted = nullptr;
    Animation* ca_completed = nullptr;
    Animation* fs_ready = nullptr;
    Animation* fs_attack = nullptr;
    Animation* ss_ready = nullptr;
    Animation* ss_attack = nullptr;

    Skill* skill1 = nullptr;
    Skill* skill2 = nullptr;
    Skill* skill3 = nullptr;
    Skill* skill4 = nullptr;

    Charge* charge = nullptr;

    Patterns* patterns = nullptr;

    Timer* delay = nullptr;

    random_device rd;

    list<Animation*> anim_list;
    list<Skill*> skill_list;

    Hpbar* profile;

    float range_x = 0;
    float speed_x = 0;
    float x_axis = 0;

    bool can_attack = false;
    bool first_flag = true;

    // Object을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void onCollisionStay(Collider* col) override;
    virtual void onCollisionExit(Collider* col) override;
};