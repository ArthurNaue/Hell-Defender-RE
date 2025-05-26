#ifndef TOWER_H
#define TOWER_H

#define TOWER_SIZE 64

#include "raylib.h"

typedef struct Tower {
    Vector2 pos;
    float size;
    Color color;
    Rectangle rec;
    Image img;
    Texture2D tex;
} Tower;

void InitTower(Tower *tower);
void DrawTower(Tower tower);

#endif
