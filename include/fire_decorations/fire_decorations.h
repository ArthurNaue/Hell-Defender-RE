#ifndef FIRE_DECORATIONS_H
#define FIRE_DECORATIONS_H

#include "raylib.h"
#include "animated_sprite/animated_sprite.h"

typedef struct FireDecoration
{
	AnimatedSprite animSprite;
	Vector2 pos;
} FireDecoration;

void InitFireDecoration(FireDecoration *fireDecoration, Vector2 pos);
void UpdateFireDecoration(FireDecoration *fireDecoration);
void DrawFireDecoration(FireDecoration fireDecoration);

#endif
