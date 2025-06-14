#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "raylib.h"
#include "dt/dt.h"

typedef struct AnimatedSprite 
{
	Image img;
	Texture tex;
	Vector2 pos;
	int frameWidth;
	int frameHeight;
	float frameTime;
	Rectangle frameRec;
	int numFrames;
	int currentFrame;
	float updateTime;
} AnimatedSprite;

void InitAnimatedSprite(AnimatedSprite *animatedSprite, Image img, int numFrames, float updateTime);
void UpdateAnimatedSprite(AnimatedSprite *animatedSprite);
void UpdateAnimatedSpritePos(AnimatedSprite *animatedSprite, Vector2 pos);
void DrawAnimatedSprite(AnimatedSprite animatedSprite);
void SetAnimatedSpriteDir(AnimatedSprite *animatedSprite, int facingRight);
void UnloadAnimatedSpriteTex(AnimatedSprite *animatedSprite);

#endif
