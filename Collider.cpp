#include "DXUT.h"
#include "Collider.h"

Collider::Collider()
	:isEnable(true), m_tag(Tag::NONE_TAG)
{
}

Collider::Collider(Tag tag)
	:isEnable(true), m_tag(tag)
{
	overlap_rect = { 1,1,1,1 };
	collision = this;
}

Collider::~Collider()
{

}

void Collider::Draw(char r, char g, char b)
{
	if (draw_flag)
	{
		if (isEnable)
		{
			LPD3DXLINE line;

			D3DXCreateLine(g_device, &line);

			line->SetWidth(1);
			line->SetAntialias(true);
			line->Begin();

			Vector2* ver = new Vector2[5];
			ver[0] = Vector2((float)right, (float)top);
			ver[1] = Vector2((float)right, (float)bottom);
			ver[2] = Vector2((float)left, (float)bottom);
			ver[3] = Vector2((float)left, (float)top);
			ver[4] = Vector2((float)right, (float)top);

			line->Draw(ver, 5, RGB(r, g, b));

			SAFE_DELETE_ARRAY(ver);

			line->End();
			//line->OnLostDevice();
			line->Release();
		}
	}
}

void Collider::SetRange(Vector2 pos, float width, float height)
{
	if (this != nullptr)
	{
		m_pos = pos;
		left = pos.x - width / 2;
		right = pos.x + width / 2;
		top = pos.y - height / 2;
		bottom = pos.y + height / 2;
	}
}

void Collider::ColliderInit(Object* owner, Collider** col, ObjectTag tag, float damage, bool isEnable)
{
	(*col) = new Collider(tag);
	(*col)->lpGameObject = owner;
	(*col)->damage = damage;
	(*col)->isEnable = isEnable;
	OBJECT->AddCollsion((*col));
}
