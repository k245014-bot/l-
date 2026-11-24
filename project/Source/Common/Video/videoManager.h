#pragma once
#include "../Object/object2D.h"
#include <map>

class VideoManager :public Object2D
{
public:
	VideoManager();
	~VideoManager();
	void Update()override;
	void Draw()override;

	void Play(const int& _index);
	void LoopPlay(const int& _index);
	void LoopPlay(const int& _index,const int& startTime, const int& endTime);
	void Stop(const int& _index);

	bool IsPlay(const int& _index) { return GetMovieTotalFrameToGraph(videoData[_index].hImage) == TRUE; }
	void Load(const int& _index, const std::string& _fileName);
	void Delete(const int& _index);



private:

	struct Video_Data
	{
		bool active;
		VECTOR3 position;
		int hImage;
	};

	std::map<int, Video_Data> videoData;


};
