#include <stdlib.h>
#include "tower/tower.h"

//FUNCTION TO INITIALIZE TOWER
void InitTower(Tower *tower) 
{
	//DEFINES TOWER PARAMETERS
	tower->pos = (Vector2){300 - (TOWER_SIZE/2), 300 - (TOWER_SIZE/2)};
	tower->size = TOWER_SIZE;
	tower->color = GREEN;
	tower->rec = (Rectangle){tower->pos.x, tower->pos.y,  tower->size, tower->size};
	tower->attackRec = (Rectangle){0, 0, 64, 64};
	tower->attackImg = LoadImage("assets/images/tower/attack/towerAttack.png");
	tower->attackTex = LoadTextureFromImage(tower->attackImg);
	tower->isAttacking = 0;
	tower->img = LoadImage("assets/images/tower/tower.png");
	tower->tex = LoadTextureFromImage(tower->img);

	UnloadImage(tower->img);
	UnloadImage(tower->attackImg);
}

//FUNCTION TO DRAW TOWER
void DrawTower(Tower tower) 
{
	//DRAW TOWERS TEXTURE
	DrawTextureV(tower.tex, tower.pos, WHITE);
}

//FUNCTION USED TO ATTACK WITH M1
void TowerAttack(Tower *tower)
{
	tower->isAttacking = 1;

	//GETS THE CURSOR POSITION
	Vector2 mousePosition = GetMousePosition();

	//UPDATES TOWER ATTACK RECTANGLE
	tower->attackRec.x = mousePosition.x - (tower->attackRec.width/2);
	tower->attackRec.y = mousePosition.y - (tower->attackRec.height/2);

	//DRAW ATTACK RECTANGLE TO SCREEN
	DrawTextureV(tower->attackTex, (Vector2){tower->attackRec.x, tower->attackRec.y}, WHITE);
}
