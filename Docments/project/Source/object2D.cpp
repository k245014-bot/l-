#include "object2D.h"

Object2D::Object2D()
{
	hImage = -1;
	position = VECTOR2(0, 0);
	velocity = VECTOR2(0, 0);
	rotation = 0;
	scale = 0;
}

Object2D::~Object2D()
{
	if (resourceKeep == false)
	{
		DeleteImage();
	}
}

void Object2D::Draw()
{
	DrawGraph(position.x, position.y, hImage, true);
}


void Object2D::LoadhImage(const std::string& handle)
{
	//参照渡ししたhandleをMV1LoadModelの引数に合うようにポインタに変換する
	const char* copy = handle.c_str();
	//変換した文字列を読み込み
	hImage = LoadGraph(copy);
}

void Object2D::DeleteImage()
{
	DeleteGraph(hImage);
}
