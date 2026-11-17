#pragma once
#include "../Object/objectBase.h"

class EffectBase :public ObjectBase
{
public:
	EffectBase();
	~EffectBase();
	void Update()override;
	void Draw()override;

	//virtual void Create(VECTOR2 in_pos, int in_handle, float in_speed);
	//virtual void Stop();
	//virtual void LOOP();

private:

	struct EffectData
	{
		VECTOR2 pos;
		int handle;
		int time;
		bool active;
		float speed;
		int playHandle;
	};

	EffectData effect;
};
