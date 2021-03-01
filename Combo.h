#pragma once
#include "Animation.h"
class Combo
{
private:
	static int REF_COUNT;

	list<Animation*> combo_list;
	BYTE bind_key;

	list<Animation*>::iterator iter;

	Timer* next_combo_timer;

	Object* owner;

	UINT index;

	bool isNextCombo;
public:
	Combo(Object* owner, BYTE key)
		:bind_key(key), owner(owner)
	{
		next_combo_timer = new Timer;
		next_combo_timer->setTimer(1);

		isNextCombo = false;
		index = 0;

		combo_list.clear();
		iter = combo_list.begin();

		REF_COUNT++;
	}
	~Combo()
	{
		combo_list.clear();
		SAFE_DELETE(next_combo_timer);
		REF_COUNT--;
		Debug("---------------------------------- [ ~Combo()     REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
		if (REF_COUNT == 0)
			Debug("Combo REF_COUNT is ZERO!");
	}
	void AddCombo(Animation* combo)
	{
		combo_list.emplace_back(combo);
		iter = combo_list.begin();
	}
	void RemoveCombo(Animation* combo)
	{
		combo_list.remove(combo);
		iter = combo_list.begin();
	}
	void RemoveAllCombo()
	{
		combo_list.clear();
		iter = combo_list.begin();
	}
	void ComboUpdate(Timer** timer);
	void ComboRender();
	void AllIsKeyFalse();
	bool IsKey();
	int Index();
	int Frame();
};