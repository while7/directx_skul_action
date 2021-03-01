#pragma once
#include "singleton.h"
class World : public singleton<World>
{
public:
	World();
	~World();
};

#define WORLD World::GetInstance()