#include "tower/towerAttack/towerAttack.h"
#include "dt/dt.h"

char attackCooldownText[32];

void InitTowerAttack(TowerAttack *towerAttack) 
{
	AnimatedSprite animSprite;
	InitAnimatedSprite(&animSprite, LoadImage("assets/images/tower/tower_attack/tower_attack.png"), 2, 0.5f);

	towerAttack->size = TOWERATTACK_SIZE;
	towerAttack->rec = (Rectangle){0, 0, towerAttack->size, towerAttack->size};
	towerAttack->animSprite = animSprite;
	towerAttack->cooldown = TOWERATTACK_COOLDOWN;
	towerAttack->isAttacking = 0;
}

void DrawTowerAttack(TowerAttack towerAttack) 
{
	DrawAnimatedSprite(towerAttack.animSprite);
}

void UpdateAttack(TowerAttack *towerAttack)
{
	UpdateAnimatedSprite(&towerAttack->animSprite);
	UpdateAnimatedSpritePos(&towerAttack->animSprite, (Vector2){towerAttack->rec.x, towerAttack->rec.y});
	
	if(towerAttack->isAttacking==1)
	{
		DrawTowerAttack(*towerAttack);
	}

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

void TurnAttackOn(TowerAttack *towerAttack)
{
	towerAttack->isAttacking = 1;
	HideCursor();
}

void TurnAttackOff(TowerAttack *towerAttack)
{
	towerAttack->isAttacking = 0;
	ShowCursor();
}

void ResetAttackCooldown(TowerAttack *towerAttack)
{
	towerAttack->cooldown = TOWERATTACK_COOLDOWN;
}
