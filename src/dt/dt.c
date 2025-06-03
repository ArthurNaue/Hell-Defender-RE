#include "raylib.h"
#include "dt/dt.h"

float dt = 0.0f;

void UpdateDt(void)
{
	dt = GetFrameTime();
}
