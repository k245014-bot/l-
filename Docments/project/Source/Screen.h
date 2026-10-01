#pragma once

/// <summary>
/// Window‚Ì’è‹`‚ð‚µ‚Ü‚·
/// </summary>
namespace Screen
{
	static const int WIDTH = 872;
	static const int HEIGHT = 1280;
	static const BOOL WINDOW_MODE = TRUE;
	static const char* WINDOW_NAME = "project";
	static const float WINDOW_EXTEND = 1.0f;
};

struct ScreenData 
{
	int x, y;
	int bit;
};