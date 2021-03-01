#include "DXUT.h"
#include "IngameScene.h"
#include "Player.h"
#include "Enemy.h"

void IngameScene::Init()
{
	OBJECT->AddObject("mouse", new Mouse, center_vec2, MOUSE);

	setting = new UiWindow("setting", VK_ESCAPE, { 1, 1}, { 0,10 });

	bg = IMAGE->FindImage("bg");

	CAMERA->Reset();
	CAMERA->m_vCameraPos = { 0,10 };

	Player* player = new Player;
	OBJECT->AddObject("player", player, { 0,10 }, PLAYER);

	OBJECT->AddObject("enemy", new Enemy(EnemyType::Article), { 20,160 }, ENEMY);
	OBJECT->AddObject("enemy", new Enemy(EnemyType::Hunter), { 30,160 }, ENEMY);
	OBJECT->AddObject("enemy", new Enemy(EnemyType::Wizard), { 40,160 }, ENEMY);

	enemy_spawn_count = 0;
	boss_flag = false;
	stage1_flag = true;
}

void IngameScene::Update()
{
	setting->WindowUpdate();

	if (setting->isOpen())
	{
		if (INPUT->KeyDown(VK_BACK))
		{
			PostQuitMessage(0);
		}
		TIME->TimeScale = 0;
	}
	else
	{
		TIME->TimeScale = 1;
	}

	mt19937 gen(rd());
	uniform_int_distribution<int> spawn_x(-500, 590);

	if (stage1_flag)
	{
		if (enemy_spawn_count <= 10)
		{
			if (OBJECT->ObjList[ENEMY].size() == 0)
			{
				enemy_spawn_count++;
				OBJECT->AddObject("enemy", new Enemy(EnemyType::Article), { (float)spawn_x(gen),160 }, ENEMY);
				OBJECT->AddObject("enemy", new Enemy(EnemyType::Hunter), { (float)spawn_x(gen),160 }, ENEMY);
				OBJECT->AddObject("enemy", new Enemy(EnemyType::Wizard), { (float)spawn_x(gen),160 }, ENEMY);
			}
		}
		else
		{
			if (!boss_flag)
			{
				boss_flag = true;
				OBJECT->AddObject("Boss", new Enemy(EnemyType::Boss), { 0,160 }, ENEMY);
			}
		}
	}
}

void IngameScene::Render()
{
	bg->CenterRender({ 0,10 }, 0, { 1.6f,1.6f },1);
	setting->WindowRender();
}

void IngameScene::Release()
{
	SAFE_DELETE(setting);
}
