#include "fire_decorations/fire_decorations.h"

int fireDecorationNumber = 0;
FireDecoration *fireDecorationsList = NULL;

void CreateFireDecoration(void)
{
	int numberOfFires = (rand() % 4) + 1;

	for(int i=0; i<numberOfFires; i++)
	{
		FireDecoration fire;
		Vector2 fireDecorationPos = {(rand() % 600) + 1, (rand() % 600) + 1};
		InitFireDecoration(&fire, fireDecorationPos);
	}
}

void InitFireDecoration(FireDecoration *fireDecoration, Vector2 pos)
{
	fireDecorationNumber++;

	AnimatedSprite animSprite;

	InitAnimatedSprite(&animSprite, LoadImage("assets/images/decorations/fire.png"), 2, 0.5f);

	fireDecoration->animSprite = animSprite;
	fireDecoration->pos = pos;

	UpdateAnimatedSpritePos(&fireDecoration->animSprite, pos);

	UpdateFireDecorationsList(*fireDecoration, &fireDecorationsList);
}

void UpdateFireDecorationsList(FireDecoration fire, FireDecoration **fireDecorationsList)
{
	*fireDecorationsList = realloc(*fireDecorationsList, sizeof(FireDecoration) * fireDecorationNumber);
	(*fireDecorationsList)[fireDecorationNumber - 1] = fire;
}

void DrawFireDecorations(void)
{
	for(int i=0; i<fireDecorationNumber; i++)
	{
		FireDecoration *fire = &fireDecorationsList[i];
		UpdateAnimatedSprite(&fire->animSprite);
		DrawAnimatedSprite(fireDecorationsList[i].animSprite);
	}
}
