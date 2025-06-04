#include "animated_sprite/animated_sprite.h"
#include "raylib.h"

void InitAnimatedSprite(AnimatedSprite *animatedSprite)
{
	animatedSprite->img = LoadImage("assets/images/tower/towerAttack/towerAttack.png");
	animatedSprite->tex = LoadTextureFromImage(animatedSprite->img);
	animatedSprite->pos = (Vector2){300, 450};
	animatedSprite->frameWidth = 64;
	animatedSprite->frameHeight = 64;
	animatedSprite->frameTime = 0.0f;
	animatedSprite->frameRec = (Rectangle){0, 0, animatedSprite->frameWidth, animatedSprite->frameHeight};
	animatedSprite->numFrames = 2;
	animatedSprite->currentFrame = 0;
	animatedSprite->updateTime = 0.2f;

	UnloadImage(animatedSprite->img);
}

void UpdateAnimatedSprite(AnimatedSprite *animatedSprite)
{
	animatedSprite->frameTime += dt;
	if(animatedSprite->frameTime >= animatedSprite->updateTime)
	{
		animatedSprite->frameTime = 0.0f;
		animatedSprite->currentFrame++;
		if(animatedSprite->currentFrame >= animatedSprite->numFrames){animatedSprite->currentFrame=0;}

		animatedSprite->frameRec.x = (float){animatedSprite->currentFrame * animatedSprite->frameWidth};
	}
}

void DrawAnimatedSprite(AnimatedSprite animatedSprite)
{
	DrawTextureRec(animatedSprite.tex, animatedSprite.frameRec, animatedSprite.pos, WHITE);
}
