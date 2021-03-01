#pragma once
class Skill
{
private:
	static int REF_COUNT;
	Object* owner;
	BYTE key;
	map<UINT,function<void()>> frame_evnet_list;
	map<UINT, function<void()>>::iterator iter;
public:
	Animation* skill_anim;

	Skill(Object* owner, const string& name, BYTE key = VK_PAD_A)
		:owner(owner), key(key)
	{
		skill_anim = new Animation(owner, name);
		skill_anim->SetTime();
		skill_anim->isKey = false;
		REF_COUNT++;
	}
	~Skill()
	{
		SAFE_DELETE(skill_anim);
		REF_COUNT--;
		Debug("---------------------------------- [ ~Skill()     REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
		if (REF_COUNT == 0)
			Debug("Skill REF_COUNT is ZERO!");
	}

	void AddFrameEvent(UINT min, UINT max, function<void()> func);
	void SkillUpdate(Timer** timer);
	void SkillRender(Vector2 add = { 0,0 });
};