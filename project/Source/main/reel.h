#pragma once
#include "../object2D.h"
#include <vector>
#include <map>

namespace
{
	static const int POS_X_WAIT = 160;
	static const int POS_Y_WAIT = 60;
	static const int REEL_MAX = 3;
	static const float LOOP_TIME = 0.78f;
	static const float STOP_WAIT_TIME = 0.19f;
	static const float RESET_WAIT_TIME = 0.5f;
	static const float SYMBOL_SIZE = 66.0f;
	static const int MAX_SYMBOL = 20;
	static const int MAX_LINE = 8;
}

class CsvReader;
class ImageSynthesis;
class MainControl;
class Random;
class ReelTableBase;

class Reel :public Object2D
{
public:
	Reel(MainControl* data);
	~Reel();
	void Update()override;
	void Draw()override;
	void SetPush(int index, bool active);
	void SetSymbol(int symbol);
	
	std::vector<std::vector<int>> GetReel() { return reel; }
	int GetCell(int index) { return reelData[index].cell; }

private:

	enum Reel_ID
	{
		LEFT,
		MIDDLE,
		RIGHT,
		ID_NUM
	};

	CsvReader* csv;
	ImageSynthesis* is;
	MainControl* mainData;
	Random* rand;
	ReelTableBase* reelTable[Reel_ID::ID_NUM];

	std::vector<std::vector<int>> reel;
	std::vector<std::vector<int>> symbol;
	std::map<int, int> symbolHandle;
	std::map<int, std::vector<std::vector<int>>> hitSymbolLines;

	std::map<int, std::vector<int>> reachLine;

	float GetStopLine(std::map<int, std::vector<std::vector<int>>> data, int frames);

	struct ReelData
	{
		enum STOP_LINE
		{
			UP = 1,
			MIDDLE = 2,
			DOWN = 3
		};


		float scroll;
		int cell;
		int symbolListImage;
		int brackSymbolListImage;
		bool stop;
		float stopSpeed;
		bool slip;
		bool slipStop;
		int prevFrame;
		int currentFrame;
		float snapStart;
		float snapTarget;
		int slipCount;
		bool push;
		int stopLine;
		int symbolIndex;

		ReelData() :scroll(0), cell(0), symbolListImage(0), brackSymbolListImage(0), stop(false), stopSpeed(0),
			slip(false), slipStop(false), prevFrame(0), currentFrame(0), snapStart(0), snapTarget(0),
			slipCount(0), push(false), stopLine(0), symbolIndex(-1) {
		}
	};

	ReelData reelData[Reel_ID::ID_NUM];

	int imageW;	//テクスチャの横幅を取得
	int	imageH;	//テクスチャの縦幅を取得

	int reelH;

	bool first;


	float resetTime;

	int hitSymbol;
	int pushWaitTime;

	int stopIndex;

	int reachSymbol;

	int reelCover;

	void Reset();
	void Speen(int index);
	void Stop(int index);
	void Gap(int index);
	void Scroll();
	float CalcNearScroll(float in_scroll);
	void ShitSelect(int index);
	//小役の滑りコマ数の検索
	void SearchSymbol(int index, int in_symbol);
	void ScrollCheck(int index);
	void FlameMove(int index);
	//小役の判定
	void SymbolAligned();

	void ReelReset(int index);

	bool AllSlipStop();
	bool AllReelStop();

	int GetSymbolFrame(int frame);


};

