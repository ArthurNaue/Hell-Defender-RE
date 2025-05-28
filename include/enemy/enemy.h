#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "tower/tower.h"

//DEFINES THE ENEMY STRUCTURE
typedef struct Enemy {
    Vector2 pos;
    float speed;
    float size;
    Color color;
    Rectangle rec;
    Image img;
    Texture2D tex;
} Enemy;

//DEFINES THE ENEMY FUNCTIONS
void InitEnemy(Enemy *enemy);
void DrawEnemy(Enemy enemy);
void MoveEnemy(Enemy *enemy, Tower *tower);
void UpdateEnemyRec(Enemy *enemy);

#endif
