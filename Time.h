#pragma once
#include "singleton.h"
class Time :
    public singleton<Time>
{
public:
    static float TimeScale;
};

#define TIME Time::GetInstance()