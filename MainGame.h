#pragma once
class MainGame
{
public:
	MainGame();
	virtual ~MainGame();

	void Init();
	void Update();
	void Render();
	void Release();
	void LostDevice();
	void ResetDevice();
};

