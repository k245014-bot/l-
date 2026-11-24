#pragma once
#include "../Object/objectBase.h"


class EffectBase :public ObjectBase
{
public:
	EffectBase();
	virtual ~EffectBase();
	virtual void Update()override {};
	virtual void Draw()override {};

	virtual void Stop();
	virtual void LOOP();
	virtual void SetPosition(VECTOR3 in_pos);
	virtual bool GetActive() { return effect.active; }

	void Delete() { effect.active = false; }
	

protected:

	struct EffectData
	{
		VECTOR3 pos;
		VECTOR3* chasePos;
		VECTOR3 scale;
		int handle;
		int time;
		bool active;
		float speed;
		int playHandle;
	};

	EffectData effect;
};

class Effect2D :public EffectBase
{
public:
	Effect2D();
	~Effect2D();
	void Update()override;

	void Create(VECTOR2 in_pos, VECTOR2* in_chasePos, VECTOR2 in_scale, int in_handle, float in_speed);

private:



};

class Effect3D :public EffectBase
{
public:
	Effect3D();
	~Effect3D();
	void Update()override;

	void Create(VECTOR3 in_pos, VECTOR3* in_chasePos, VECTOR3 in_scale, int in_handle, float in_speed);

private:

	

};

class VideoManager;

class AfterEffect :public EffectBase
{
public:
	AfterEffect();
	~AfterEffect();
	void Update()override;
	void Draw()override;

	void Create(VECTOR3 in_pos, int in_handle, bool isLoop);
	void Create(VECTOR3 in_pos, int in_handle, int startTime, int endTime);

	void ReStart();
	void Stop()override;

private:

	VideoManager* video;

};