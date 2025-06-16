#include "tower/tower.h"

Tower tower;

//FUNCTION TO INITIALIZE TOWER
void InitTower(Tower *tower) 
{
	//DEFINES TOWER PARAMETERS
	tower->pos = (Vector2){300 - (TOWER_SIZE/2), 300 - (TOWER_SIZE/2)};
	tower->color = GREEN;
	tower->rec = (Rectangle){tower->pos.x + 24, tower->pos.y + 16,  78, 108};
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
