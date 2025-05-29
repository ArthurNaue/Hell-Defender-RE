#ifndef TOWER_H
#define TOWER_H

//DEFINES THE TOWER SIZE
#define TOWER_SIZE 128

#include "raylib.h"

//DEFINES THE TOWER STRUCTURE
typedef struct Tower {
    Vector2 pos;
    float size;
    Color color;
    Rectangle rec;
    Image img;
    Texture2D tex;
} Tower;

//DEFINES THE TOWER FUNCTIONS
void InitTower(Tower *tower);
void DrawTower(Tower tower);

#endif
