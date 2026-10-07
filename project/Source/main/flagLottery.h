#pragma once
#include "../objectBase.h"


namespace
{
	//小役確率
	static const float BELLA_RAND = MAX_RAND / 8.2f;			//ベル
	static const float BELLB_RAND = MAX_RAND / 39.7f;		//ベル

	static const float BONUS_BELL_RAND = MAX_RAND / 1.0f;			//ボーナスベル
	static const float REPLAY_RAND = MAX_RAND / 7.3f;			//リプレイ
	static const float CHERRY_WEAK_RAND = MAX_RAND / 60.0f;		    //弱チェリー
	static const float CHERRY_STRONG_RAND = MAX_RAND / 327.7f;        //強チェリー

	static const float WATERMELON_RAND = MAX_RAND / 79.9f;			//スイカ
	static const float CHANCE_RAND = MAX_RAND / 512.0f;			//チャンス目
	static const float BELL_ORDER_RAND = MAX_RAND / 5.96f;			//押し順ベル

	
	}

class FlagLottery :public ObjectBase
{
public:
	FlagLottery();
	~FlagLottery();
	void Update()override;
	void Draw()override {};


private:

};
