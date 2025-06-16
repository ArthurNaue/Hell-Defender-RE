#include "tower/tower_attack/tower_attack.h"
#include "dt/dt.h"

TowerAttack towerAttack;

void InitTowerAttack(TowerAttack *towerAttack) 
{
	AnimatedSprite animSpriteActive;
	InitAnimatedSprite(&animSpriteActive, LoadImage("assets/images/tower/tower_attack/tower_attack_active.png"), 2, 0.5f);
	towerAttack->animSpriteActive = animSpriteActive;

	AnimatedSprite animSpriteUnnactive;
	InitAnimatedSprite(&animSpriteUnnactive, LoadImage("assets/images/tower/tower_attack/tower_attack_unnactive.png"), 2, 0.5f);
	towerAttack->animSpriteUnnactive = animSpriteUnnactive;

	towerAttack->size = TOWERATTACK_SIZE;
	towerAttack->rec = (Rectangle){0, 0, towerAttack->size/2, towerAttack->size/2};
	towerAttack->cooldown = TOWERATTACK_COOLDOWN;
	towerAttack->isAttacking = 0;
}

void DrawTowerAttack(TowerAttack towerAttack) 
{
	if(towerAttack.cooldown>0){DrawAnimatedSprite(towerAttack.animSpriteUnnactive);}
	else{DrawAnimatedSprite(towerAttack.animSpriteActive);}
}

void UpdateTowerAttack(TowerAttack *towerAttack)
{
	if(towerAttack->cooldown>0)
	{
		UpdateAnimatedSprite(&towerAttack->animSpriteUnnactive);
		UpdateAnimatedSpritePos(&towerAttack->animSpriteUnnactive, (Vector2){towerAttack->rec.x - towerAttack->size/4, towerAttack->rec.y - towerAttack->size/4});
	}
	else
	{
		UpdateAnimatedSprite(&towerAttack->animSpriteActive);
		UpdateAnimatedSpritePos(&towerAttack->animSpriteActive, (Vector2){towerAttack->rec.x - towerAttack->size/4, towerAttack->rec.y - towerAttack->size/4});
	}

	if(towerAttack->isAttacking==1){DrawTowerAttack(*towerAttack);}

	if(towerAttack->cooldown>0){towerAttack->cooldown-= (1 * dt);}

	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){TurnAttackOn(towerAttack);}
	else{TurnAttackOff(towerAttack);}

	Vector2 mousePosition = GetMousePosition();

	towerAttack->rec.x = mousePosition.x - towerAttack->size/4;
	towerAttack->rec.y = mousePosition.y - towerAttack->size/4;
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
