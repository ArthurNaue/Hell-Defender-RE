#ifndef TOWERATTACK_H
#define TOWERATTACK_H

#define TOWERATTACK_SIZE 64

#include "raylib.h"
#include "tower/tower.h"

//DEFINES THE TOWER STRUCTURE
typedef struct TowerAttack {
    float size;
    Rectangle rec;
    Image img;
    Texture2D tex;
    int isAttacking;
} TowerAttack;

//DEFINES THE TOWER FUNCTIONS
void InitTowerAttack(TowerAttack *towerAttack);
void DrawTowerAttack(TowerAttack *towerAttack);
void Attack(TowerAttack *towerAttack);

#endif
