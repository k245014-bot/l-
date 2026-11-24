#include "effectBase.h"
#include <EffekseerForDXLib.h>
#include "../Video/videoManager.h"

EffectBase::EffectBase()
{
}

EffectBase::~EffectBase()
{
}

void EffectBase::Stop()
{
}

void EffectBase::LOOP()
{
}

void EffectBase::SetPosition(VECTOR3 in_pos)
{
	SetPosPlayingEffekseer3DEffect(effect.playHandle, in_pos.x, in_pos.y, in_pos.z);
}

Effect3D::Effect3D()
{
}

Effect3D::~Effect3D()
{
}

void Effect3D::Update()
{
	if (effect.active == false)
	{
		return;
	}

	if (effect.chasePos == nullptr)
	{
		SetPosPlayingEffekseer3DEffect(effect.playHandle, effect.pos.x, effect.pos.y, effect.pos.z);
	}
	else
	{
		SetPosPlayingEffekseer3DEffect(effect.playHandle, effect.chasePos->x, effect.chasePos->y, effect.chasePos->z);
	}

	//Ä¶‘¬“x‚ð•Ï‚¦‚é
	SetSpeedPlayingEffekseer3DEffect(effect.playHandle, effect.speed);

	//‘å‚«‚³‚ð•Ï‚¦‚é
	SetScalePlayingEffekseer3DEffect(effect.playHandle, effect.scale.x, effect.scale.y, effect.scale.z);

}

void Effect3D::Create(VECTOR3 in_pos, VECTOR3* in_chasePos, VECTOR3 in_scale, int in_handle, float in_speed)
{
	if (effect.active == true)
	{
		return;
	}

	effect.pos = in_pos;
	effect.chasePos = in_chasePos;
	effect.scale = in_scale;
	effect.handle = in_handle;
	effect.speed = in_speed;
	effect.playHandle = PlayEffekseer3DEffect(effect.handle);
	effect.active = true;
}

Effect2D::Effect2D()
{
}

Effect2D::~Effect2D()
{
}

void Effect2D::Update()
{
	if (effect.active == false)
	{
		return;
	}

	if (effect.chasePos == nullptr)
	{
		SetPosPlayingEffekseer2DEffect(effect.playHandle, effect.pos.x, effect.pos.y, effect.pos.z);
	}
	else
	{
		SetPosPlayingEffekseer2DEffect(effect.playHandle, effect.chasePos->x, effect.chasePos->y, effect.chasePos->z);
	}

	//Ä¶‘¬“x‚ð•Ï‚¦‚é
	SetSpeedPlayingEffekseer2DEffect(effect.playHandle, effect.speed);

	//‘å‚«‚³‚ð•Ï‚¦‚é
	SetScalePlayingEffekseer2DEffect(effect.playHandle, effect.scale.x, effect.scale.y, effect.scale.z);
}

void Effect2D::Create(VECTOR2 in_pos, VECTOR2* in_chasePos, VECTOR2 in_scale, int in_handle, float in_speed)
{
	if (effect.active == true)
	{
		return;
	}

	effect.pos = VECTOR3(in_pos.x, in_pos.y, 0);
	effect.scale = VECTOR3(in_pos.x, in_pos.y, 0);
	effect.handle = in_handle;
	effect.speed = in_speed;
	effect.playHandle = PlayEffekseer2DEffect(effect.handle);
	effect.active = true;

}

AfterEffect::AfterEffect()
{
	video = new VideoManager();
}

AfterEffect::~AfterEffect()
{
	delete video;
}

void AfterEffect::Update()
{
}

void AfterEffect::Draw()
{
	video->Draw();
}

void AfterEffect::Create(VECTOR3 in_pos, int in_handle, bool isLoop)
{
	if (effect.active == true)
	{
		return;
	}

	effect.pos = VECTOR3(in_pos.x, in_pos.y, 0);
	effect.handle = in_handle;
	video->SetPosition(VECTOR2(in_pos.x, in_pos.y));

	if (isLoop == false)
	{
		
		video->Play(effect.handle);
	}
	else
	{
		video->LoopPlay(effect.handle);
	}

	effect.active = true;
}

void AfterEffect::Create(VECTOR3 in_pos, int in_handle, int startTime, int endTime)
{
	if (effect.active == true)
	{
		return;
	}

	effect.pos = VECTOR3(in_pos.x, in_pos.y, 0);
	effect.handle = in_handle;
	video->SetPosition(VECTOR2(in_pos.x, in_pos.y));

	video->LoopPlay(in_handle, startTime, endTime);

	effect.active = true;
}

void AfterEffect::Stop()
{
	if (video->IsPlay(effect.handle)== false)
	{
		return;
	}

	video->Stop(effect.handle);
}

void AfterEffect::ReStart()
{
	if (video->IsPlay(effect.handle) == true)
	{
		return;
	}

	video->Play(effect.handle);
}


