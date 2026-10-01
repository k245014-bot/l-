#pragma once
#include "../Library/myDxLib.h"
#include <map>
#include <vector>

//画像の構成
class ImageSynthesis 
{
public:
	ImageSynthesis();
	~ImageSynthesis();


	/// <summary>
	/// 画像を合わせる
	/// </summary>
	/// <param name="baseImage">ベースの画像</param>
	/// <param name="addImage">合わせる画像</param>
	/// <returns>画像のハンドラ</returns>
	int Create(int baseImage, int addImage);
	//増やしただけ
	int Create(int graph1, int graph2, int graph3, int graph4);

	/// <summary>
	/// 画像を合わせる
	/// </summary>
	/// <returns>画像のハンドラ</returns>
	int Create(int baseImage,std::vector<std::vector<int>> list, std::map<int, int> handle,int index,float wait);

private:


	std::vector<std::vector<int>> symbol;
	std::map<int, int> symbolHandle;

};
