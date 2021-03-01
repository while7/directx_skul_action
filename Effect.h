#pragma once
class Effect
{
private:
    static int REF_COUNT;
public:
    Effect(Object* owner)
    {
        REF_COUNT++;
    }
    ~Effect()
    {
        REF_COUNT--;
        Debug("---------------------------------- [ ~Effect()    REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
        if (REF_COUNT == 0)
            Debug("Effect REF_COUNT is ZERO!");
    }
};

