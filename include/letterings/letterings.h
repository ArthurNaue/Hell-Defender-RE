#ifndef LETTERING_H
#define LETTERING_H

#include "raylib.h"

typedef struct Lettering
{
	Image img;
	Texture2D tex;
} Lettering;

extern Lettering titleLettering;

void InitLettering(Lettering *lettering, Image img);
void DrawLettering(Texture2D letteringTex, Vector2 pos);
void UnloadLetteringTex(Texture2D *letteringTex);

#endif
