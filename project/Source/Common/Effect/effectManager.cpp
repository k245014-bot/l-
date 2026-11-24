#include "effectManager.h"
#include <EffekseerForDXLib.h>

EffectManager::EffectManager()
{
	//ハンドルの初期化
	for (auto itr : effectData)
	{
		itr.resource = -1;
	}

}

EffectManager::~EffectManager()
{
	//ハンドルの初期化
	for (auto itr : effectData)
	{
		DeleteEffekseerEffect(itr.resource);
	}
}

void EffectManager::Create(VECTOR pos, int id, VECTOR* chasePos, float speed, float scale)
{
}

void EffectManager::Update()
{

	if (effect.empty() == false)
	{
		for (auto itr = effect.begin(); itr != effect.end();)
		{
			if ((*itr)->GetActive() == false)
			{
				(*itr)->DestroyMe();
				itr = effect.erase(itr);
			}
			else
				itr++;
		}
	}

	//Effekseer更新
	UpdateEffekseer3D();
}

void EffectManager::Draw()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	//Effekseer描画
	DrawEffekseer3D();
}
