#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "animated_sprite/animated_sprite.h"
#include "points/points.h"

#define ENEMY_SIZE 64
#define ENEMY_NUMBER 2

//CREATES THE VARIABLES THAT CONTROLS ENEMY SPEED
extern int speedMultiplier;

//DEFINES THE ENEMY STRUCTURE
typedef struct Enemy 
{
	int health;
	Vector2 pos;
	float speed;
	float size;
	Rectangle rec;
	AnimatedSprite animSprite;
} Enemy;

//DEFINES THE ENEMY FUNCTIONS
void InitEnemy(Enemy *enemy);
void DrawEnemy(Enemy enemy);
void UpdateEnemySpeed(Enemy *enemy);
void MoveEnemy(Enemy *enemy);
void UpdateEnemyRec(Enemy *enemy);
void DamageEnemy(Enemy *enemy);

#endif
