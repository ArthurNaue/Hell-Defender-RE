#include "window_config/window_config.h"

int game = 1;

void StartWindow(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	Image windowImg = LoadImage("assets/images/window/icon.png"); 
	SetWindowIcon(windowImg);
	UnloadImage(windowImg);
}
