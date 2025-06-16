#ifndef TOWER_H
#define TOWER_H

#define TOWER_SIZE 120

#include "raylib.h"

typedef struct Tower {
    Vector2 pos;
    Color color;
    Rectangle rec;
    Image img;
    Texture2D tex;
} Tower;

extern Tower tower;

void InitTower(Tower *tower);
void DrawTower(Tower tower);

#endif
