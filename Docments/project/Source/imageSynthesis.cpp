#include "imageSynthesis.h"

ImageSynthesis::ImageSynthesis()
{
}

ImageSynthesis::~ImageSynthesis()
{
}


int ImageSynthesis::Create(int baseImage, int addImage)
{
	int graph;
	int width ;
	int height;
	
	GetGraphSize(baseImage, &width, &height);
	graph = MakeScreen(width, height, true);
	SetDrawScreen(graph);
	DrawGraph(0, 0, baseImage, true);
	DrawGraph(0, 0, addImage, true);
	SetDrawScreen(DX_SCREEN_BACK);

	return graph;
}

int ImageSynthesis::Create(int graph1, int graph2, int graph3, int graph4)
{
	int graph;
	int width;
	int height;

	GetGraphSize(graph1, &width, &height);
	graph = MakeScreen(width, height, true);
	SetDrawScreen(graph);
	DrawGraph(0, 0, graph1, true);
	DrawGraph(0, 0, graph2, true);
	DrawGraph(0, 60, graph3, true);
	DrawGraph(0, 120, graph4, true);
	SetDrawScreen(DX_SCREEN_BACK);

	return graph;
}

int ImageSynthesis::Create(int baseImage, std::vector<std::vector<int>> list, std::map<int, int> handle, int index,float wait)
{
	int graph;
	int width;
	int height;

	GetGraphSize(baseImage, &width, &height);
	graph = MakeScreen(width, height, true);
	SetDrawScreen(graph);
	
	for (auto itr : handle)
	{
		for (int y = 0; y < list.size(); y++)
		{
			for (int x = 0; x < index; x++)
			{
				if (x != index - 1)
				{
					continue;
				}

				int symbolIndex = list[y][x];

				if (symbolIndex == itr.first)
				{
					if (symbolIndex == 7 || symbolIndex == 8 || symbolIndex == 9)
					{
						DrawGraph(0, (int)wait * y, itr.second, true);
					}
					else
					{
						DrawGraph(10, (int)wait * y, itr.second, true);
					}
					
				}
			}
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return graph;
}

