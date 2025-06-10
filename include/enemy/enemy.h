#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "animated_sprite/animated_sprite.h"
#include "points/points.h"
#include "tower/tower.h"
#include "tower/tower_attack/tower_attack.h"

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

extern int enemiesAlive;
extern Enemy *enemiesList;

//DEFINES THE ENEMY FUNCTIONS
void CreateEnemy(void);
void InitEnemy(Enemy *enemy);
void UpdateEnemiesList(Enemy enemy, Enemy **enemiesList);
void DrawEnemies(void);
void UpdateEnemySpeed(Enemy *enemy);
void MoveEnemies(void);
void UpdateEnemyRec(Enemy *enemy);
void CheckForEnemyDamage(TowerAttack *towerAttack);
void DamageEnemy(Enemy *enemy);
void RemoveEnemy(int index);
void SpawnEnemy(Enemy *enemy);
void DeleteEnemies(void);

#endif
