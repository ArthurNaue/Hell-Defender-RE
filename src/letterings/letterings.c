#include "letterings/letterings.h"

Lettering titleLettering;

void InitLettering(Lettering *lettering, Image img)
{
	lettering->img = img;
	lettering->tex = LoadTextureFromImage(lettering->img);
	UnloadImage(lettering->img);
}

void DrawLettering(Texture2D letteringTex, Vector2 pos)
{
	DrawTextureV(letteringTex, pos, WHITE);
}

void UnloadLetteringTex(Texture2D *letteringTex)
{
	UnloadTexture(*letteringTex);
}
