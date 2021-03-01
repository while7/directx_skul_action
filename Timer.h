#pragma once
#include "singleton.h"
class Timer
{
public:
	Timer();
	~Timer();

	bool Update();
	void LockUpdate();

	float m_start = 0;
	float m_delay = 0;

	bool isLock;

	void setTimer(float vel) { m_delay = vel; }
};
