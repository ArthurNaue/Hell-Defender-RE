#ifndef TOWERATTACK_H
#define TOWERATTACK_H

#define TOWERATTACK_SIZE 64
#define TOWERATTACK_COOLDOWN 60

#include "raylib.h"
#include "animated_sprite/animated_sprite.h"
#include "tower/tower.h"

extern char attackCooldownText[32];

//DEFINES THE TOWER STRUCTURE
typedef struct TowerAttack 
{
    float size;
    Rectangle rec;
    AnimatedSprite animSpriteActive;
    AnimatedSprite animSpriteUnnactive;
    int cooldown;
    int isAttacking;
} TowerAttack;

//DEFINES THE TOWER FUNCTIONS
void InitTowerAttack(TowerAttack *towerAttack);
void DrawTowerAttack(TowerAttack towerAttack);
void UpdateAttack(TowerAttack *towerAttack);
void TurnAttackOn(TowerAttack *towerAttack);
void TurnAttackOff(TowerAttack *towerAttack);
void ResetAttackCooldown(TowerAttack *towerAttack);

#endif
