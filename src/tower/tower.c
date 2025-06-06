#include "tower/tower.h"

//FUNCTION TO INITIALIZE TOWER
void InitTower(Tower *tower) 
{
	//DEFINES TOWER PARAMETERS
	tower->pos = (Vector2){300 - (TOWER_SIZE_X/2), 300 - (TOWER_SIZE_Y/2)};
	tower->color = GREEN;
	tower->rec = (Rectangle){tower->pos.x + TOWER_PADDING_X, tower->pos.y + TOWER_PADDING_Y,  TOWER_SIZE_X, TOWER_SIZE_Y};
	tower->img = LoadImage("assets/images/tower/tower.png");
	tower->tex = LoadTextureFromImage(tower->img);

	UnloadImage(tower->img);
}

//FUNCTION TO DRAW TOWER
void DrawTower(Tower tower) 
{
	//DRAW TOWERS TEXTURE
	DrawTextureV(tower.tex, tower.pos, WHITE);
}
