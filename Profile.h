#pragma once
class Profile
{
private:
	static int REF_COUNT;
	Object* owner;
	texture* profile;
	texture* bar;
public:
	Profile(Object* owner);
	~Profile();
	void ProfileRender();
};