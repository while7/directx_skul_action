#pragma once
class Patterns
{
private:
	int alpha = 255;

	bool case1 = true;
	bool case2 = true;
	bool case3 = true;
	bool case4 = true;
	bool case5 = true;
	bool case6 = true;

	bool appear_flag = true;

	float x_scale = 1;

	Object* owner = nullptr;
	Object* player = nullptr;

	Animation* appear = nullptr;
	Animation* attack_a = nullptr;
	Animation* attack_b = nullptr;
	Animation* attack_c = nullptr;
	Animation* dash = nullptr;
	Animation* diagonal = nullptr;
	Animation* diagonal_fin = nullptr;
	Animation* disappear = nullptr;
	Animation* idle = nullptr;
	Animation* rush = nullptr;
	Animation* slash_h = nullptr;
	Animation* slash_v = nullptr;

	Timer* delay = nullptr;

	vector<Animation*> anim_list;
public:
private:
	bool HpPerIsIn(int max_per, int min_per);
	bool IsIdle();
	bool Appear(bool idle_flag = false);
	bool Disappear();

	bool SetAppear(bool idle_flag = false);

	bool Case1(bool& flag);
	bool Case2(bool& flag);

	/// <summary>
	/// 아직 사용하면 안됨
	/// </summary>
	/// <returns></returns>
	bool Case3();

	/// <summary>
	/// 아직 사용하면 안됨
	/// </summary>
	/// <returns></returns>
	bool Case4();

	/// <summary>
	/// 아직 사용하면 안됨
	/// </summary>
	/// <returns></returns>
	bool Case5();

	/// <summary>
	/// 아직 사용하면 안됨
	/// </summary>
	/// <returns></returns>
	bool Case6();
public:
	Patterns(Object* owner);
	~Patterns();
	void Update();
	void Render();
};