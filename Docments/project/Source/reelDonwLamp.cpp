#include "reelDonwLamp.h"

ReelDownLamp::ReelDownLamp(std::string filename):LampBase(filename)
{

	SetDrawOrder(90);
	lampes[0].image = LoadGraph("data/texture/botan/Left_1.png");
	lampes[0].position = VECTOR2(200.914, 773.308);

	lampes[1].image = LoadGraph("data/texture/botan/Center_1.png");
	lampes[1].position = VECTOR2(370.827, 774.0f);

	lampes[2].image = LoadGraph("data/texture/botan/Right_1.png");
	lampes[2].position = VECTOR2(543.968, 775.510);

	for (int i = 0; i < 3; i++)
	{
		lampes[i].active = false;
	}
}

ReelDownLamp::~ReelDownLamp()
{
	for (int i = 0; i < 3; i++)
	{
		DeleteGraph(lampes[i].image);
	}
}

void ReelDownLamp::Update()
{
}

void ReelDownLamp::Draw()
{
	if (lampes[0].active == false)
	{
		DrawGraph(lampes[0].position.x, lampes[0].position.y, lampes[0].image, true);
	}

	if (lampes[1].active == false)
	{
		DrawGraph(lampes[1].position.x, lampes[1].position.y, lampes[1].image, true);
	}

	if (lampes[2].active == false)
	{
		DrawGraph(lampes[2].position.x, lampes[2].position.y, lampes[2].image, true);
	}

}
