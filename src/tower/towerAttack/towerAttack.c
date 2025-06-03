#include "tower/towerAttack/towerAttack.h"
#include "dt/dt.h"

char attackCooldownText[32];

void InitTowerAttack(TowerAttack *towerAttack) 
{
	towerAttack->size = TOWERATTACK_SIZE;
	towerAttack->rec = (Rectangle){0, 0, towerAttack->size, towerAttack->size};
	towerAttack->img = LoadImage("assets/images/tower/towerAttack/towerAttack.png");
	towerAttack->tex = LoadTextureFromImage(towerAttack->img);
	towerAttack->cooldown = TOWERATTACK_COOLDOWN;
	towerAttack->isAttacking = 0;

	UnloadImage(towerAttack->img);
}

void DrawTowerAttack(TowerAttack *towerAttack) 
{
	//DRAW THE ATTACK TEXTURE
	DrawTextureV(towerAttack->tex, (Vector2){towerAttack->rec.x, towerAttack->rec.y}, WHITE);
}

void UpdateAttack(TowerAttack *towerAttack)
{
	if(towerAttack->cooldown>0)
	{
		towerAttack->cooldown-= (1 * dt);
	}

	//GETS THE CURSOR POSITION
	Vector2 mousePosition = GetMousePosition();

	//UPDATES TOWER ATTACK RECTANGLE
	towerAttack->rec.x = mousePosition.x - (towerAttack->rec.width/2);
	towerAttack->rec.y = mousePosition.y - (towerAttack->rec.height/2);
}

void ResetAttackCooldown(TowerAttack *towerAttack)
{
	towerAttack->cooldown = TOWERATTACK_COOLDOWN;
}
