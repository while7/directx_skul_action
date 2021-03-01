#pragma once
#include "Scene.h"
class IngameScene :
    public Scene
{
    texture* bg;

    random_device rd;

    UiWindow* setting;

    int enemy_spawn_count = 0;

    bool stage1_flag = false;
    bool boss_flag = false;

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

