#ifndef TOWER_H
#define TOWER_H

//DEFINES THE TOWER SIZE
#define TOWER_SIZE_X 80
#define TOWER_SIZE_Y 112
#define TOWER_PADDING_X 24
#define TOWER_PADDING_Y 16

#include "raylib.h"

//DEFINES THE TOWER STRUCTURE
typedef struct Tower {
    Vector2 pos;
    Color color;
    Rectangle rec;
    Image img;
    Texture2D tex;
} Tower;

//DEFINES THE TOWER FUNCTIONS
void InitTower(Tower *tower);
void DrawTower(Tower tower);

#endif
