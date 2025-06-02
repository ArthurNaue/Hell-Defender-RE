#include "tower/towerAttack/towerAttack.h"

void InitTowerAttack(TowerAttack *towerAttack) 
{
	towerAttack->size = TOWERATTACK_SIZE;
	towerAttack->rec = (Rectangle){0, 0, towerAttack->size, towerAttack->size};
	towerAttack->img = LoadImage("assets/images/tower/towerAttack/towerAttack.png");
	towerAttack->tex = LoadTextureFromImage(towerAttack->img);
	towerAttack->isAttacking = 0;

	UnloadImage(towerAttack->img);
}

void DrawTowerAttack(TowerAttack *towerAttack) 
{
	DrawTextureV(towerAttack->tex, (Vector2){towerAttack->rec.x, towerAttack->rec.y}, WHITE);
}

void Attack(TowerAttack *towerAttack)
{
	towerAttack->isAttacking = 1;

	//GETS THE CURSOR POSITION
	Vector2 mousePosition = GetMousePosition();

	//UPDATES TOWER ATTACK RECTANGLE
	towerAttack->rec.x = mousePosition.x - (towerAttack->rec.width/2);
	towerAttack->rec.y = mousePosition.y - (towerAttack->rec.height/2);
}
