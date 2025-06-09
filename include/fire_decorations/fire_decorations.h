#ifndef FIRE_DECORATIONS_H
#define FIRE_DECORATIONS_H

#include "stdlib.h"
#include "raylib.h"
#include "animated_sprite/animated_sprite.h"

typedef struct FireDecoration
{
	AnimatedSprite animSprite;
	Vector2 pos;
} FireDecoration;

extern int fireDecorationNumber;
extern FireDecoration *fireDecorationList;

void CreateFireDecoration(void);
void InitFireDecoration(FireDecoration *fireDecoration, Vector2 pos);
void UpdateFireDecorationsList(FireDecoration fire, FireDecoration **fireDecorationList);
void DrawFireDecorations(void);

#endif
