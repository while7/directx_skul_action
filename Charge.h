#pragma once
class Charge
{
private:
    static int REF_COUNT;

    Object* owner;

    vector<Animation*> charge_list;
    vector<Animation*>::iterator iter;
public:
    enum ChargeLevel
    {
        PREPARE = 0,
        ANTICIPATION,
        CHARGING,
        CHARGED,
        INCOMPLETED,
        COMPLETED,
    };

    Charge(Object* owner, Animation* prepare, Animation* anticipation, Animation* charging, Animation* charged, Animation* incompleted, Animation* completed)
        :owner(owner)
    {
        charge_list.clear();

        charge_list.emplace_back(prepare);
        charge_list.emplace_back(anticipation);
        charge_list.emplace_back(charging);
        charge_list.emplace_back(charged);
        charge_list.emplace_back(incompleted);
        charge_list.emplace_back(completed);

        iter = charge_list.begin();

        end_flag = true;
        cancel_flag = false;

        REF_COUNT++;
    }
    ~Charge()
    {
        for (auto& iter : charge_list)
        {
            SAFE_DELETE(iter);
        }

        charge_list.clear();

        REF_COUNT--;
        Debug("---------------------------------- [ ~Charge()    REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
        if (REF_COUNT == 0)
            Debug("Charge REF_COUNT is ZERO!");
    }
    void ChargeUpdate();
    void ChargeRender(Vector2 pos, Vector2 size);
    void ChargeCancel();
    void Start();
    bool IsKey();

    bool end_flag = true;
    bool cancel_flag = false;
};