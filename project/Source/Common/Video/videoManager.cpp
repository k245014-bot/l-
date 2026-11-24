#include "videoManager.h"

VideoManager::VideoManager()
{
}

VideoManager::~VideoManager()
{
}

void VideoManager::Update()
{
}

void VideoManager::Draw()
{
	for (auto itr : videoData)
	{
		if (IsPlay(itr.second.hImage) == false)
		{
			continue;
		}

		DrawGraph(position.x, position.y, itr.second.hImage, true);
	}

}

void VideoManager::Play(const int& _index)
{
	//‚È‚ñ‚à“ü‚Á‚Ä–³‚©‚Á‚½‚ç
	if (videoData.empty() == true)
	{
		return;
	}

	PlayMovieToGraph(videoData.at(_index).hImage, DX_MOVIEPLAYTYPE_NORMAL);


	videoData.at(_index).active = true;
}

void VideoManager::LoopPlay(const int& _index)
{
	//‚È‚ñ‚à“ü‚Á‚Ä–³‚©‚Á‚½‚ç
	if (videoData.empty() == true)
	{
		return;
	}


	if (GetMovieStateToGraph(videoData.at(_index).hImage) == false)
	{
		SeekMovieToGraph(videoData.at(_index).hImage, 0);
		PlayMovieToGraph(videoData.at(_index).hImage);
	}

	videoData.at(_index).active = true;
}

void VideoManager::LoopPlay(const int& _index, const int& startTime, const int& endTime)
{
	//‚È‚ñ‚à“ü‚Á‚Ä–³‚©‚Á‚½‚ç
	if (videoData.empty() == true)
	{
		return;
	}

	if (GetMovieStateToGraph(videoData.at(_index).hImage) == false)
	{
		PlayMovieToGraph(videoData.at(_index).hImage);
		SeekMovieToGraph(videoData.at(_index).hImage, startTime);
	}

	if (TellMovieToGraph(videoData.at(_index).hImage) >= endTime)
	{
		SeekMovieToGraph(videoData.at(_index).hImage, startTime);
	}

	videoData.at(_index).active = true;

}

void VideoManager::Stop(const int& _index)
{
	PauseMovieToGraph(videoData.at(_index).hImage);

	videoData.at(_index).active = true;
}

void VideoManager::Load(const int& _index, const std::string& _fileName)
{
	Video_Data data;
	data.hImage = LoadGraph(_fileName.c_str());

	videoData.insert({ _index,  data });

	videoData.at(_index).active = true;
}

void VideoManager::Delete(const int& _index)
{
	videoData.at(_index).active = false;
	PauseMovieToGraph(videoData.at(_index).hImage);
}
