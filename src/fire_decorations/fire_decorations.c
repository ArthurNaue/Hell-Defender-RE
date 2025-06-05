#include "fire_decorations/fire_decorations.h"

void InitFireDecoration(FireDecoration *fireDecoration, Vector2 pos)
{
	AnimatedSprite animSprite;

	InitAnimatedSprite(&animSprite, LoadImage("assets/images/decorations/fire.png"), 2, 0.5f);

	fireDecoration->animSprite = animSprite;
	fireDecoration->pos = pos;

	UpdateAnimatedSpritePos(&fireDecoration->animSprite, pos);
}

void UpdateFireDecoration(FireDecoration *fireDecoration)
{
	UpdateAnimatedSprite(&fireDecoration->animSprite);
}

void DrawFireDecoration(FireDecoration fireDecoration)
{
	DrawAnimatedSprite(fireDecoration.animSprite);
}
