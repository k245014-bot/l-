#pragma once
#include "../Object/objectBase.h"
#include "../Effect/effectBase.h"
#include <vector>

namespace effect
{
	static const int EFFECT_MAX = 1000;

	struct EffectData
	{
		VECTOR3 position;	//座標
		int resource;		//ハンドル
		float speed;		//速度
	};
}

class EffectManager :public ObjectBase
{
public:
	EffectManager();
	~EffectManager();
	void Create(VECTOR pos, int id, VECTOR* chasePos, float speed, float scale);
	//void Create(VECTOR3)
	void Update()override;
	void Draw()override;

private:
	
	std::vector<effect::EffectData> effectData;

	
	std::vector<EffectBase*> effect;

};

