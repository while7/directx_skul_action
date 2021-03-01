#pragma once
class Animation
{
public:
	static int REF_COUNT;
	Animation(Object* owner, const string& key)
		:anim(), anim_timer(), index(0), isKey(false), owner(owner)
	{
		SetAnim(key);

		anim_timer = new Timer;

		SetTime();

		REF_COUNT++;
	}

	~Animation()
	{
		SAFE_DELETE(anim_timer);

		REF_COUNT--;
		Debug("---------------------------------- [ ~Animation() REF_COUNT : %2d ] ----------------------------------", REF_COUNT);
		if (REF_COUNT == 0)
			Debug("Animation REF_COUNT is ZERO!");
	}

	void SetTime(float delay = 0.1f)
	{
		anim_timer->setTimer(delay);
	}

	void SetAnim(const string& key)
	{
		anim = IMAGE->FINDVECIMAGE(key);
	}

	void AnimUpdate()
	{
		if (isKey)
			if (anim_timer->Update())
				index++;
	}

	void AnimRender(Vector2 pos, float rotate, Vector2 size = { 1,1 }, bool isContinue = true, D3DCOLOR color = RGBA(255, 255, 255, 255))
	{
		if (index >= anim->GetSize())
		{
			if (!isContinue)
				isKey = false;
			index = 0;
		}

		if (isKey)
		{
			anim->FINDIMAGE(index)->CenterRender(pos, D3DXToDegree(rotate), size, (1 / owner->vPos.y) <= 0 ? 0 : (1 / owner->vPos.y), color);
		}
	}

	VECtexture* anim = nullptr;
	Timer* anim_timer = nullptr;
	Object* owner = nullptr;

	int index;
	bool isKey;
};