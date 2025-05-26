#include "tower/tower.h"

void InitTower(Tower *tower) 
{
    tower->pos = (Vector2){300 - (TOWER_SIZE/2), 300 - (TOWER_SIZE/2)};
    tower->size = TOWER_SIZE;
    tower->color = GREEN;
    tower->rec = (Rectangle){tower->pos.x, tower->pos.y,  tower->size, tower->size};
    tower->img = LoadImage("assets/images/tower/tower.png");
    tower->tex = LoadTextureFromImage(tower->img);
    UnloadImage(tower->img);
}

void DrawTower(Tower tower) 
{
	DrawTextureV(tower.tex, tower.pos, WHITE);
}
