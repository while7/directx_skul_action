#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
    texture* bg;
    texture* key_bg;

    int alpha;

    bool down_flag;

    bool how_to_play_flag = false;

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};