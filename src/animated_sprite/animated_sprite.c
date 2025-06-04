#include "animated_sprite/animated_sprite.h"
#include "raylib.h"

void InitAnimatedSprite(AnimatedSprite *animatedSprite, Image img, int numFrames, float updateTime)
{
	animatedSprite->img = img;
	animatedSprite->tex = LoadTextureFromImage(animatedSprite->img);
	animatedSprite->pos = (Vector2){800, 800};
	animatedSprite->frameWidth = 64;
	animatedSprite->frameHeight = 64;
	animatedSprite->frameTime = 0.0f;
	animatedSprite->numFrames = numFrames;
	animatedSprite->currentFrame = 0;
	animatedSprite->updateTime = updateTime;
	animatedSprite->frameRec = (Rectangle){0, 0, animatedSprite->frameWidth, animatedSprite->frameHeight};

	UnloadImage(animatedSprite->img);
}

void UpdateAnimatedSprite(AnimatedSprite *animatedSprite, int facingRight)
{
	animatedSprite->frameTime += dt;
	if(animatedSprite->frameTime >= animatedSprite->updateTime)
	{
		animatedSprite->frameTime = 0.0f;
		animatedSprite->currentFrame++;
		if(animatedSprite->currentFrame >= animatedSprite->numFrames){animatedSprite->currentFrame=0;}

		animatedSprite->frameRec.x = (float){animatedSprite->currentFrame * animatedSprite->frameWidth};
	}

	if(facingRight==1){animatedSprite->frameRec.width = animatedSprite->frameWidth;}
	else{animatedSprite->frameRec.width = -animatedSprite->frameWidth;}
}

void UpdateAnimatedSpritePos(AnimatedSprite *animatedSprite, Vector2 pos)
{
	animatedSprite->pos = pos;
}

void DrawAnimatedSprite(AnimatedSprite animatedSprite)
{
	DrawTextureRec(animatedSprite.tex, animatedSprite.frameRec, animatedSprite.pos, WHITE);
}
