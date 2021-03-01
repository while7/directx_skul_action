#include "DXUT.h"
#include "Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

void Mouse::Init()
{
	col = new Collider;
	col->lpGameObject = this;
	col->UnEnable();
	OBJECT->AddCollsion(col);
}

void Mouse::Update()
{
	//dir += 0.01;
	//if (dir >= 360)
		dir = 0;
	col->SetRange(CAMERA->WorldToView(vPos), 25, 25);

	vPos = INPUT->GetMousePos();
}

void Mouse::Render()
{
	if (col->isEnable)
		IMAGE->FindImage("MousePoint")->CenterRender(vPos, dir, {0.05f,0.05f});
	col->Draw(255, 0, 0);
}

void Mouse::Release()
{
	SAFE_DELETE(col);
}

void Mouse::onCollisionStay(Collider* col)
{

}

void Mouse::onCollisionExit(Collider* col)
{
}
